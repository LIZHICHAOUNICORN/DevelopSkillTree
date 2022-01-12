#!/usr/bin/env/python3
"""
seq2seq model recipe

"""

import torch
import torch.nn as nn
import torch.optim as optim

import spacy
import numpy as np

import random
import math
import time
import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

SEED = 1234
random.seed(SEED)
np.random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.backends.cudnn.deterministic = True

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')


class Encoder(nn.Module):

    def __init__(self, vocab_size, emb_dim, hid_dim, n_layers, dropout):
        super().__init__()

        self.hid_dim = hid_dim
        self.n_layers = n_layers

        self.embedding = nn.Embedding(vocab_size, emb_dim)
        self.rnn = nn.LSTM(emb_dim,
                           hid_dim,
                           n_layers,
                           dropout=dropout,
                           batch_first=True)

        self.dropout = nn.Dropout(dropout)

    def forward(self, src):
        """
        src shape: [batch-size, seqlen]
        embedded shape: [batch-size, seqlen, emb_dim]
        outputs shape: [batch-size, seqlen, hid_dim]
        hidden shape: [n_layers, batch-size, hid_dim]
        cell: [n_layers, batch-size, hid_dim]
        """

        embedded = self.dropout(self.embedding(src))

        outputs, (hidden, cell) = self.rnn(embedded)

        return hidden, cell


class Decoder(nn.Module):

    def __init__(self, vocab_size, emb_dim, hid_dim, n_layers,
                 dropout):
        super().__init__()

        self.output_dim = vocab_size
        self.hid_dim = hid_dim
        self.n_layers = n_layers

        self.embedding = nn.Embedding(vocab_size, emb_dim)
        self.rnn = nn.LSTM(emb_dim,
                           hid_dim,
                           n_layers,
                           dropout=dropout,
                           batch_first=False)

        self.fc_out = nn.Linear(hid_dim, vocab_size)
        self.dropout = nn.Dropout(dropout)

    def forward(self, input, hidden, cell):
        """
        input shape: [seq-len]
        hidden shape: []
        """
        # input shape: [1, batch-size]
        input = input.unsqueeze(0)

        # input shape: [1, batch-size, emb_dim]
        input = self.dropout(self.embedding(input))
        # hidden shape: [batch-size, seq-len, hid_dim]
        # cell shape: [batch-size, seq-len, hid_dim]
        output, (hidden, cell) = self.rnn(input, (hidden, cell))

        prediction = self.fc_out(output.squeeze(0))

        return prediction, hidden, cell


class Seq2Seq(nn.Module):

    def __init__(self, encoder, decoder, device):
        super().__init__()

        self.encoder = encoder
        self.decoder = decoder

        self.device = device

        assert encoder.hid_dim == decoder.hid_dim, "Hidden dimensions of encoder of decoder must be equal!"
        assert encoder.n_layers == decoder.n_layers, "Encoder and decoder must have equal number of layers"

    def get_next_token(self, x, hidden, cell):

        output, hidden, cell = self.decoder(x, hidden, cell)
        top_v = torch.argmax(output, axis=-1)

        return top_v, output, hidden, cell




    def forward(self, src, trg, tearcher_forcing_radio=0.8):
        """
        src shape: [batch-size, seqlen]
        trg shape: [batch-size, seqlen]
        """

        batch_size = trg.shape[0]
        trg_len = trg.shape[1]

        trg_vocab_size = self.decoder.output_dim
        logging.debug("batch size: {}, target len: {}, vocab_size: {}".format(
            batch_size, trg_len, trg_vocab_size))

        outputs = torch.zeros(trg_len, batch_size,
                              trg_vocab_size).to(self.device)

        hidden, cell = self.encoder(src)

        # input = trg[0, :]
        input = trg.transpose(0, 1)[0, :]

        for t in range(1, trg_len):

            output, hidden, cell = self.decoder(input, hidden, cell)
            outputs[t] = output
            teacher_force = random.random() < tearcher_forcing_radio
            top_1 = output.argmax(1)
            intput = trg[t] if teacher_force else top_1

        return outputs
