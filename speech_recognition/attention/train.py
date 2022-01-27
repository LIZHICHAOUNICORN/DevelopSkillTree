#!/usr/bin/env/python3
""" 
Library implementing attention model.

Authors
* Zhichao Li 2022

"""

import torch
import torch.nn as nn
import torch.optim as optim

import spacy
import numpy as np

from dataio import SRC, TGT, train_iterator, valid_iterator
from models import Seq2Seq, Encoder, Decoder
from utils import initialize_weights, count_parameters, epoch_time

import random
import math
import time
from tqdm import tqdm
import logging

# TODO(zhichaoli) remove this to yaml
FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

SEED = 1234
random.seed(SEED)
np.random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.backends.cudnn.deterministic = True

INPUT_DIM = vocab_size = len(SRC.vocab)
OUT_DIM = vocab_size = len(TGT.vocab)
HID_DIM = 256
ENC_LAYER = 2
DEC_LAYER = 2
ENC_HEADS = 4
DEC_HEADS = 4
ENC_PF_DIM = 128
DEC_PF_DIM = 128
ENC_DROPOUT = 0.1
DEC_DROPOUT = 0.1
EPOCH_NUM = 1000
LOG_INTERVAL = 10
CKPT_DIR = "exp/checkpoints/{}"


device = torch.device("cuda:0")

def train(model, iterator, optimizer, criterion):
    model.train()
    epoch_loss = 0

    for i, batch in tqdm(enumerate(iterator)):
        src = batch.src.to(device)
        tgt = batch.trg.to(device)

        optimizer.zero_grad()
        output, _ = model(src, tgt[:, :-1])
        output_dim = output.shape[-1]

        output = output.contiguous().view(-1, output_dim)
        tgt = tgt[:, 1:].contiguous().view(-1)

        loss = criterion(output, tgt)
        loss.backward()
        optimizer.step()

        epoch_loss += loss.item()

    return epoch_loss / len(iterator)


def evaluate(model, iterator, criterion):
    model.eval()
    epoch_loss = 0
    with torch.no_grad():
        for i, batch in tqdm(enumerate(iterator)):
            src = batch.src.to(device)
            tgt = batch.trg.to(device)

            output, _ = model(src, tgt[:, :-1])
            output_dim = output.shape[-1]

            output = output.contiguous().view(-1, output_dim)
            tgt = tgt[:, 1:].contiguous().view(-1)

            loss = criterion(output, tgt)
            epoch_loss = loss.item()

    return epoch_loss / len(iterator)


if __name__ == "__main__":
    device = torch.device("cuda:0")
    encoder = Encoder(INPUT_DIM, HID_DIM, ENC_LAYER, ENC_HEADS, ENC_PF_DIM,
                      ENC_DROPOUT)
    logging.debug("encoder: {}".format(encoder))

    decoder = Decoder(OUT_DIM, HID_DIM, DEC_LAYER, DEC_HEADS, DEC_PF_DIM,
                      DEC_DROPOUT, device)
    logging.debug("decoder: {}".format(decoder))

    SRC_PAD_IDX = SRC.vocab.stoi[SRC.pad_token]
    TGT_PAD_IDX = TGT.vocab.stoi[TGT.pad_token]

    model = Seq2Seq(encoder, decoder, SRC_PAD_IDX, TGT_PAD_IDX,
                    device).to(device)
    model.apply(initialize_weights)
    para_num = count_parameters(model)
    logging.info("The model has {} trainable parameters".format(para_num))

    LEARNING_RATE = 0.0005
    optim = torch.optim.Adam(model.parameters(), lr=LEARNING_RATE)

    criterion = nn.CrossEntropyLoss(ignore_index=TGT_PAD_IDX)

    best_valid_loss = float("inf")

    for epoch in range(1, EPOCH_NUM):
        start_time = time.time()

        train_loss = train(model, train_iterator, optim, criterion)
        valid_loss = evaluate(model, valid_iterator, criterion)

        end_time = time.time()

        epoch_mins, epoch_secs = epoch_time(start_time, end_time)

        logging.info(
            "epoch: {} train loss: {} eval loss: {}, epoch time: {} mins - {} secs "
            .format(epoch, train_loss, valid_loss, epoch_mins, epoch_secs))

        if valid_loss < best_valid_loss:
            best_valid_loss = valid_loss
            ckpt_name = "{}.pt".format(epoch)
            torch.save(model.state_dict(), CKPT_DIR.format(ckpt_name))
