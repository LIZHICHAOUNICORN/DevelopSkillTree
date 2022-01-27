#!/usr/bin/env/python3
""" 
The inference script

Authors
* Zhichao Li 2022

"""

import torch
import torch.nn as nn
import torch.optim as optim

import spacy
import numpy as np

from models import Seq2Seq, Encoder, Decoder
from arguments import parse_arguments
from dataio import train_data, SRC, TGT

import random
import math
import time
import yaml
import logging

# TODO(zhichaoli) remove this to yaml
FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


def translate_sentence(sentence,
                       src_field,
                       tgt_field,
                       model,
                       device,
                       max_len=50):
    model.eval()

    if isinstance(sentence, str):
        nlp = spacy.load("de_core_news_sm")
        tokens = [token.text.lower() for token in nlp(sentence)]
    else:
        tokens = [token.lower() for token in sentence]

    tokens = [src_field.init_token] + tokens + [src_field.eos_token]

    src_indexes = [src_field.vocab.stoi[token] for token in tokens]

    src_tensor = torch.LongTensor(src_indexes).unsqueeze(0).to(device)
    src_mask = model.make_src_mask(src_tensor)

    with torch.no_grad():
        enc_src = model.encoder(src_tensor, src_mask)

    tgt_indexes = [tgt_field.vocab.stoi[tgt_field.init_token]]

    for i in range(max_len):
        tgt_tensor = torch.LongTensor(tgt_indexes).unsqueeze(0).to(device)
        tgt_mask = model.make_tgt_mask(tgt_tensor)

        with torch.no_grad():
            output, attention = model.decoder(tgt_tensor, enc_src, tgt_mask,
                                              src_mask)

        pred_token = output.argmax(2)[:, -1].item()
        tgt_indexes.append(pred_token)

        if pred_token == tgt_field.vocab.stoi[tgt_field.eos_token]:
            break
    tgt_tokens = [tgt_field.vocab.itos[i] for i in tgt_indexes]

    return tgt_tokens[1:], attention


if __name__ == "__main__":

    args = parse_arguments()
    hparams_file = args.config
    hparams = None
    with open(hparams_file) as fin:
        hparams = yaml.load(fin, Loader=yaml.FullLoader)
    assert hparams is not None, "args.config: {} not found".format(args.config)

    device = torch.device("cuda:0")

    encoder = Encoder(hparams["input_dim"], hparams["hid_dim"],
                      hparams["encoder_layers"], hparams["encoder_heads"],
                      hparams["encoder_pf_dim"], hparams["encoder_dropout"])
    logging.debug("encoder: {}".format(encoder))

    decoder = Decoder(hparams["output_dim"], hparams["hid_dim"],
                      hparams["decoder_layers"], hparams["decoder_heads"],
                      hparams["decoder_pf_dim"], hparams["encoder_dropout"],
                      device)
    logging.debug("decoder: {}".format(decoder))

    SRC_PAD_IDX = SRC.vocab.stoi[SRC.pad_token]
    TGT_PAD_IDX = TGT.vocab.stoi[TGT.pad_token]

    model = Seq2Seq(encoder, decoder, SRC_PAD_IDX, TGT_PAD_IDX,
                    device).to(device)

    model.load_state_dict(torch.load(hparams["best_ckpt"]))

    example_idx = 8
    src = vars(train_data.examples[example_idx])["src"]
    tgt = vars(train_data.examples[example_idx])["trg"]
    logging.info("src: {}, tgt: {}".format(src, tgt))

    translation, attention = translate_sentence(src, SRC, TGT, model, device)
    logging.info("predict: {}".format(translation))
