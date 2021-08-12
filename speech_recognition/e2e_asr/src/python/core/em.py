# Author: Zhichao Li
# Time: 2021-08-04

import numpy as np
from log import get_logger

logger = get_logger()


if __name__ == '__main__':
    Q = [1, 2, 3]
    V = ['红', '白']
    A = [[0.5, 0.2, 0.3], [0.3, 0.5, 0.2], [0.2, 0.3, 0.5]]
    B = [[0.5, 0.5], [0.4, 0.6], [0.7, 0.3]]
    # O = ['红', '白', '红', '红', '白', '红', '白', '白']
    # O = ['红', '白', '红', '白']    #习题10.1的例子
    O = ['红', '白', '红']    #习题10.3的例子

    PI = [[0.2, 0.4, 0.4]]

    hmm = HMM(A=A, B=B, pi=PI)
    hmm.forward_algo(Q, V, O)
    hmm.backward_algo(Q, V, O)
    hmm.viterbi(Q, V, O)
