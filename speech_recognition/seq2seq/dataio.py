import torch
import numpy as np

import random
import string
import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


def random_string(string_len: int) -> str:
    letters = string.ascii_uppercase

    return "".join(random.choice(letters) for i in range(string_len))


def get_batch(batch_size, length):
    batched_example = [random_string(length) for i in range(batch_size)]

    enc_x = torch.tensor(
        np.array([[ord(ch) - ord('A') + 1 for ch in list(exp)]
                  for exp in batched_example]))
    y = torch.tensor(
        np.array([[o for o in reversed(e_idx)] for e_idx in enc_x.tolist()]))

    dec_x = torch.tensor(np.array([[0] + e_idx[:-1] for e_idx in y.tolist()]))

    return (batched_example, enc_x, dec_x, y)


if __name__ == "__main__":
    bz, enc_x, dec_x, y = get_batch(32, 16)
    logging.info("bz: {}".format(bz))
    logging.info("enc_x: {}, shape: {}".format(enc_x, enc_x.shape))
    logging.info("dec_x: {}, shape: {}".format(dec_x, dec_x.shape))
    logging.info("y: {}".format(y))
