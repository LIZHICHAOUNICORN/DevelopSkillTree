#!/usr/bin/env/python3
""" 

Authors
* Zhichao Li 2022

"""

import time
import logging
import torch.nn as nn
# import matplotlib.pyplot as plt

# TODO(zhichaoli) remove this to yaml
FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


def initialize_weights(model):
    if hasattr(model, "weight") and model.weight.dim() > 1:
        nn.init.xavier_uniform_(model.weight.data)


def count_parameters(model):
    return sum(p.numel() for p in model.parameters() if p.requires_grad)


def epoch_time(start_time, end_time):
    elapsed_time = end_time - start_time
    elapsed_mins = int(elapsed_time / 60)
    elapsed_secs = int(elapsed_time - (elapsed_mins) * 60)
    return elapsed_mins, elapsed_secs

def display_attention(sentence, translation, attention, n_heads, n_rows, n_cols):
    assert n_rows * n_cols == n_heads

    fig = plt.figure(figsize=(15, 25))
    for i in range(n_heads):
        ax = fig.add_subplot(n_rows, n_cols, i+1)
        _attention = attention.squeeze(0)[i].cpu().detach().numpy()

        cax = ax.matshow(_attention, cmap="bone")

        ax.tick_params(labelsize=12)
        ax.set_xticklabels([""]+ ["<sos>"] + [t.lower() for t in sentence] + ["<eos>"], rotation=45)
        ax.set_yticklabels([""]+ translation)

        ax.xaxis.set_major_locator(ticker.MultipleLocator(1))
        ax.yaxis.set_major_locator(ticker.MultipleLocator(1))

    plt.show()
    plt.close()
