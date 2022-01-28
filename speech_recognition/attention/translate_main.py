#!/usr/bin/env/python3
""" 
The start point of engine.

Authors
* Zhichao Li 2022

"""

import torch
import torch.nn as nn

import numpy as np

import time
import yaml
import logging

from dataio import SRC, TGT, train_iterator, valid_iterator
from models import Seq2Seq, Encoder, Decoder
from utils import initialize_weights, count_parameters, epoch_time
from train import train, evaluate
from arguments import parse_arguments

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

if __name__ == "__main__":

    args = parse_arguments()

    hparams_file = args.config
    hparams = None
    with open(hparams_file) as fin:
        hparams = yaml.load(fin, Loader=yaml.FullLoader)
    assert hparams is not None, "args.config: {} not found".format(args.config)

    SEED = hparams["seed"]
    np.random.seed(SEED)
    torch.manual_seed(SEED)
    torch.cuda.manual_seed(SEED)
    torch.backends.cudnn.deterministic = hparams["cudnn_deter"]

    device = torch.device(hparams["device"])

    encoder = Encoder(hparams["input_dim"],
                      hparams["hid_dim"],
                      hparams["encoder_layers"],
                      hparams["encoder_heads"],
                      hparams["encoder_pf_dim"],
                      hparams["encoder_dropout"],
                      device,
                      max_length=hparams["max_len"])

    decoder = Decoder(hparams["output_dim"],
                      hparams["hid_dim"],
                      hparams["decoder_layers"],
                      hparams["decoder_heads"],
                      hparams["decoder_pf_dim"],
                      hparams["decoder_dropout"],
                      device,
                      max_length=hparams["max_len"])

    SRC_PAD_IDX = SRC.vocab.stoi[SRC.pad_token]
    TGT_PAD_IDX = TGT.vocab.stoi[TGT.pad_token]

    model = Seq2Seq(encoder, decoder, SRC_PAD_IDX, TGT_PAD_IDX,
                    device).to(device)

    model.apply(initialize_weights)

    para_num = count_parameters(model)
    logging.info("The model has {} trainable parameters, model: {}".format(
        para_num, model))

    optim = torch.optim.Adam(model.parameters(), lr=hparams["hparas"]["lr"])

    criterion = nn.CrossEntropyLoss(ignore_index=TGT_PAD_IDX)

    best_valid_loss = float('inf')

    for epoch in range(1, hparams["hparas"]["epoch_num"]):
        start_time = time.time()

        train_loss = train(model, train_iterator, optim, criterion, device)
        valid_loss = evaluate(model, valid_iterator, criterion, device)

        end_time = time.time()

        epoch_mins, epoch_secs = epoch_time(start_time, end_time)

        logging.info(
            "epoch: {} train loss: {}, valid loss: {}, best valid loss: {},"
            "epoch time: {} mins - {} secs ".format(epoch, train_loss,
                                                    valid_loss, best_valid_loss,
                                                    epoch_mins, epoch_secs))

        if valid_loss < best_valid_loss:
            best_valid_loss = valid_loss
            ckpt_name = "{}.pt".format(epoch)
            torch.save(model.state_dict(),
                       hparams["ckpt_dir"].format(ckpt_name))
