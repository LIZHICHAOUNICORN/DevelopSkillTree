import torch
from torch.autograd import Variable

from torchtext.legacy.datasets import Multi30k
from torchtext.legacy.data import Field, BucketIterator

import numpy as np

import spacy

import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


def subsequent_mask(size):
    "Mask out subsequent positions."
    attn_shape = (1, size, size)
    subsequent_mask = np.triu(np.ones(attn_shape), k=1).astype('uint8')
    return torch.from_numpy(subsequent_mask) == 0


class Batch:
    """
    This class implements encoder for seq2seq model.

    Arguments
    ---------
    src: tensor
        input feature.

    Example
    -------
    >>> 

    """

    def __init__(self, src, tgt=None, pad=0):
        super().__init__()

        # src shape: [batch-size, seq_len]
        # tgt shape: [batch-size, seq_len]

        self.src = src
        # src_mask shape: [batch-size, 1, seq_len]
        self.src_mask = (src != pad).unsqueeze(-2)

        if tgt != None:
            # self.tgt shape: [batch-size, seq_len-1]
            self.tgt = tgt[:, :-1]
            # self.tgt_y shape: [batch-size, seq_len-1]
            self.tgt_y = tgt[:, 1:]
            # self.tgt_mask shape: [batch-size, seq_len-1, seq_len-1]
            self.tgt_mask = \
                self.make_std_mask(self.tgt, pad)
            self.ntokens = (self.tgt_y != pad).data.sum()

    @staticmethod
    def make_std_mask(tgt, pad):
        "Create a mask to hide padding and future words."
        # tgt shape: [batch-size, 1, seq_len-1]
        tgt_mask = (tgt != pad).unsqueeze(-2)
        # tgt shape: [batch-size, seq_len-1, seq_len-1]
        tgt_mask = tgt_mask & Variable(
            subsequent_mask(tgt.size(-1)).type_as(tgt_mask.data))
        return tgt_mask


def synthetic_data(vacab_size, batch, nbatches, seq_len=5):
    """

    """
    for i in range(nbatches):
        # data shape: [batch-size, seq_len]
        data = torch.from_numpy(
            np.random.randint(1, vacab_size, size=(batch, seq_len)))
        data[:, 0] = 1
        # src shape: [batch-size, seq_len]
        # tgt shape: [batch-size, seq_len]
        src = Variable(data, requires_grad=False)
        tgt = Variable(data, requires_grad=False)

        yield Batch(src, tgt, 0)


spacy_de = spacy.load("de_core_news_sm")
spacy_en = spacy.load("en_core_web_sm")


def tokenize_de(text):

    return [tok.text for tok in spacy_de.tokenizer(text)]


def tokenize_en(text):

    return [tok.text for tok in spacy_en.tokenizer(text)]


SRC = Field(tokenize=tokenize_de,
            init_token='<sos>',
            eos_token='<eos>',
            lower=True,
            batch_first=True)

TGT = Field(tokenize=tokenize_en,
            init_token='<sos>',
            eos_token='<eos>',
            lower=True,
            batch_first=True)

train_data, valid_data, test_data = Multi30k.splits(exts=('.de', '.en'),
                                                    fields=(SRC, TGT))

SRC.build_vocab(train_data, min_freq=2)
TGT.build_vocab(train_data, min_freq=2)

BATCH_SIZE = 8
train_iterator, valid_iterator, test_iterator = BucketIterator.splits(
    (train_data, valid_data, test_data), batch_size=BATCH_SIZE)

if __name__ == "__main__":
    syn_data = synthetic_data(8, 2, 1)
    for i, batch in enumerate(syn_data):
        logging.info("batch-src shape {}, batch-src: {}".format(
            batch.src.shape, batch.src))
        logging.info("batch-tgt shape {}, batch-tgt: {}".format(
            batch.tgt.shape, batch.tgt))
        logging.info("batch-src-mask shape {}, batch-src-mask: {}".format(
            batch.src_mask.shape, batch.src_mask))
        logging.info("batch-tgt-mask shape {}, batch-src-mask: {}".format(
            batch.tgt_mask.shape, batch.tgt_mask))
        logging.info("batch-tgt-y shape {}, trg_y: {}".format(
            batch.tgt_y.shape, batch.tgt_y))
