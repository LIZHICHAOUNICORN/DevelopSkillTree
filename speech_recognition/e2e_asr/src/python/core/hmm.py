# Author: Zhichao Li
# Time: 2021-07-31

import numpy as np
from log import get_logger

logger = get_logger()

class HMM:
    def __init__(self, A=None, B=None, pi=None):
        self.A = A
        self.B = B
        self.pi = pi
        self.forward_p = None
        self.forward = None
        self.betas = None
        self.backward_p = None

    def set_param(self, A, B, pi):
        self.A = A
        self.B = B
        self.pi = pi

    # 前向算法
    def forward_algo(self, Q, V, O):
        logger.info("forward algrithm")
        N = len(Q)
        M = len(O)
        T = M
        logger.debug("N: {}, M: {}, T: {}".format(N, M, T))
        alphas = np.zeros((N, M))
        for t in range(T):
            indexofO = V.index(O[t])
            for i in range(N):
                if t > 0:
                    alphas[i][t] = np.dot([alpha[t-1] for alpha in alphas], [a[i] for a in self.A]) * self.B[i][indexofO]
                else:
                    alphas[i][t] = self.B[i][indexofO] * self.pi[t][i]
                logger.debug("forward t: {}, i: {}, alphas[{}][{}]={}".format(t, i, i, t, alphas[i][t]))
        p = np.sum([alpha[T-1] for alpha in alphas])
        self.forward_p = p
        logger.info("forward final p: {}".format(p))
        self.alphas = alphas
        

    # 后向算法
    def backward_algo(self, Q, V, O):
        N = len(Q)
        M = len(O)
        T = M
        betas = np.ones((N, M))

        for t in range(T-2, -1, -1):
            indexofO = V.index(O[t+1])
            for i in range(N):
                betas[i][t] = np.dot(np.multiply(self.A[i], [b[indexofO] for b in self.B]), [beta[t+1] for beta in betas])
                logger.debug("backward t: {}, i: {}, betas[{}][{}]={}".format(t, i, i, t, betas[i][t]))

        indexofO = V.index(O[0])
        self.betas = betas
        p = np.dot(np.multiply(self.pi, [b[indexofO] for b in self.B]), [beta[0] for beta in betas])
        self.backward_p = p
        logger.info("backward final p: {}".format(p))

    # viterbi 算法
    def viterbi(self, Q, V, O):
        N = len(Q)
        M = len(O)
        T = M
        deltas = np.zeros((N, M))
        psis = np.zeros((N, M))
        I = np.zeros((1, M))
        for t in range(T):
            indexofO = V.index(O[t])
            for i in range(N):
                if t == 0:
                    deltas[i][t] = self.pi[t][i] * self.B[i][indexofO]
                    psis[i][t] = 0
                else:
                    deltas[i][t] = np.max(np.multiply([delta[t-1] for delta in deltas], [a[i] for a in self.A])) * self.B[i][indexofO]
                    psis[i][t] = np.argmax(np.multiply([delta[t-1] for delta in deltas], [a[i] for a in self.A]))
                logger.debug("i: {}, t: {}, delta[{}][{}]: {}, psis[{}][{}]: {}".format(i, t, i, t, deltas[i][t], i, t, psis[i][t]))
        I[0][T-1] = np.argmax([delta[T-1] for delta in deltas])
        for t in range(T-2, -1, -1):
            I[0][t] = psis[int(I[0][t+1])][t+1]
            logger.debug("i{} = psis{} * i{} = {}".format(t+1, t+2, t+2, I[0][t]+1))
        logger.info("best path: {}".format('->'.join(str(int(i+1)) for i in I[0])))

    # EM 算法
    def fit(self):
        pass

    # E step
    def _do_estep(self):
        pass

    # M step
    def _do_mstep(self):
        pass


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
