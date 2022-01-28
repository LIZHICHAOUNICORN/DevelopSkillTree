#!/usr/bin/env/python3
""" 
Library implementing attention model.

Authors
* Zhichao Li 2022

"""

import torch

from tqdm import tqdm
import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


def train(model, iterator, optimizer, criterion, device):
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


def evaluate(model, iterator, criterion, device):
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
