import numpy as np
import logging
from collections import defaultdict
# import pdb
from toy_nn import ToyNN


FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.DEBUG, format=FORMAT)

class CTC:
    """
    ctc 计算alpha, beta, 求导，log域操作。
    """
    def __init__(self, log_op=False, grad=True):
        self.log_op = True
        self.grad = True

    def compute_alpha(self, dist, labels):
        T, V = dist.shape
        L = len(labels)
        alpha = np.zeros([T, L])

        # Initialisation
        alpha[0, 0] = dist[0, labels[0]]
        alpha[0, 1] = dist[0, labels[1]]

        # DP, paper (6) and (7)
        for t in range(1, T):
            for i in range(L):
                s = labels[i]

                a = alpha[t-1, i]
                if i-1 >= 0:
                    a += alpha[t-1, i-1]
                # 如果label 不是blank, 
                # labels[i] != labels[i-2]，
                # 同时不在开头位置
                if i-2 >= 0 and s!= 0 and s!= labels[i-2]:
                    a += alpha[t-1, i-2]

                alpha[t, i] = a * dist[t, s]
        return alpha

    def compute_beta(self, dist, labels):
        T, V = dist.shape
        L = len(labels)
 
        # Initialisation
        beta = np.zeros([T, L])
        beta[-1, -1] = dist[-1, labels[-1]]
        beta[-1, -2] = dist[-1, labels[-2]]

        # Note: backward
        for t in range(T - 2, -1, -1):
            for i in range(L):
                s = labels[i]

                # DP paper (10) (11)
                a = beta[t + 1, i]
                if i + 1 < L:
                    a += beta[t + 1, i + 1]
                if i + 2 < L and s != 0 and s != labels[i + 2]:
                    a += beta[t + 1, i + 2]

                beta[t, i] = a * dist[t, s]
        return beta

    def gradient(self, dist, labels):
        T, V = dist.shape
        L = len(labels)
        
        alpha = self.compute_alpha(dist, labels)
        beta = self.compute_beta(dist, labels)
        p = alpha[-1, -1] + alpha[-1, -2]
        
        grad = np.zeros([T, V])
        for t in range(T):
            for s in range(V):
                lab = [i for i, c in enumerate(labels) if c == s]
                for i in lab:
                    grad[t, s] += alpha[t, i] * beta[t, i] 
                grad[t, s] /= dist[t, s] ** 2
                    
        grad /= p
        return grad

    def _logsumexp(self, a, b):
        '''
        np.log(np.exp(a) + np.exp(b))
    
        '''
        ninf = -np.float('inf')
    
        if a < b:
            a, b = b, a
    
        if b == ninf:
            return a
        else:
            return a + np.log(1 + np.exp(b - a)) 
    
    def logsumexp(self, *args):
        '''
        from scipy.special import logsumexp
        logsumexp(args)
        '''
        res = args[0]
        for e in args[1:]:
            res = self._logsumexp(res, e)
        return res

    def check_grad(self, y, labels, w=-1, v=-1, toleration=1e-3):
        grad_1 = self.gradient(y, labels)[w, v]
        
        delta = 1e-10
        original = y[w, v]
        
        y[w, v] = original + delta
        alpha = self.compute_alpha(y, labels)
        log_p1 = np.log(alpha[-1, -1] + alpha[-1, -2])
        
        y[w, v] = original - delta
        alpha = self.compute_alpha(y, labels)
        log_p2 = np.log(alpha[-1, -1] + alpha[-1, -2])
        
        y[w, v] = original
        
        grad_2 = (log_p1 - log_p2) / (2 * delta)
        if np.abs(grad_1 - grad_2) > toleration:
            logging.warning('[%d, %d]：%.2e' % (w, v, np.abs(grad_1 - grad_2)))
 
    def remove_blank(self, labels, blank=0):
        new_labels = []
    
        # combine duplicate
        previous = None
        for l in labels:
            if l != previous:
                new_labels.append(l)
                previous = l
    
        # remove blank     
        new_labels = [l for l in new_labels if l != blank]
    
        return new_labels
    
    def insert_blank(self, labels, blank=0):
        new_labels = [blank]
        for l in labels:
            new_labels += [l, blank]
        return new_labels
    
    def greedy_decode(self, y, blank=0):
        raw_rs = np.argmax(y, axis=1)
        rs = self.remove_blank(raw_rs, blank)
        return raw_rs, rs

    def beam_decode(self, dist, beam_size=10):
        T, V = dist.shape
        log_dist = np.log(dist)
    
        beam = [([], 0)]
        for t in range(T):  # for every timestep
            new_beam = []
            for prefix, score in beam:
                for i in range(V):  # for every state
                    new_prefix = prefix + [i]
                    new_score = score + log_dist[t, i]
    
                    new_beam.append((new_prefix, new_score))
    
            # top beam_size
            new_beam.sort(key=lambda x: x[1], reverse=True)
            beam = new_beam[:beam_size]
    
        return beam


    def prefix_beam_decode(self, y, beam_size=10, blank=0):
        ninf = -np.float('inf')

        T, V = y.shape
        log_y = np.log(y)
    
        beam = [(tuple(), (0, ninf))]  # blank, non-blank
        for t in range(T):  # for every timestep
            new_beam = defaultdict(lambda : (ninf, ninf))
    
            for prefix, (p_b, p_nb) in beam:
                for i in range(V):  # for every state
                    p = log_y[t, i]
    
                    if i == blank:  # propose a blank
                        new_p_b, new_p_nb = new_beam[prefix]
                        new_p_b = self.logsumexp(new_p_b, p_b + p, p_nb + p)
                        new_beam[prefix] = (new_p_b, new_p_nb)
                        continue
                    else:  # extend with non-blank
                        end_t = prefix[-1] if prefix else None
    
                        # exntend current prefix
                        new_prefix = prefix + (i,)
                        new_p_b, new_p_nb = new_beam[new_prefix]
                        if i != end_t:
                            new_p_nb = self.logsumexp(new_p_nb, p_b + p, p_nb + p)
                        else:
                            new_p_nb = self.logsumexp(new_p_nb, p_b + p)
                        new_beam[new_prefix] = (new_p_b, new_p_nb)
    
                        # keep current prefix
                        if i == end_t:
                            new_p_b, new_p_nb = new_beam[prefix]
                            new_p_nb = self.logsumexp(new_p_nb, p_nb + p)
                            new_beam[prefix] = (new_p_b, new_p_nb)
    
            # top beam_size
            beam = sorted(new_beam.items(), key=lambda x : self.logsumexp(*x[1]), reverse=True)
            beam = beam[:beam_size]
    
        return beam


def main():
    T, V = 12, 5
    m, n = 6, V
    
    x = np.random.random([T, m])
    nn = ToyNN(m, n)
    dist = nn.forward(x)
    logging.debug("dist: {}".format(dist))

    labels = [0, 3, 0, 3, 0, 4, 0]
    ctc = CTC();
    alpha = ctc.compute_alpha(dist, labels)
    logging.debug("alpha: {}".format(alpha))
    # The total probabilities of l' with and without
    # the final blank at time T.
    alpha_prob = alpha[-1, -1] + alpha[-1, -2]
    logging.info("alpha prob: {}".format(alpha_prob))

    beta = ctc.compute_beta(dist, labels)
    beta_prob = beta[0, 0] + beta[0, 1]
    logging.info("beta: {}".format(beta_prob))

    gradient = ctc.gradient(dist, labels)
    logging.debug("gradient: {}".format(gradient))
 
    # greed search
    dist = nn.softmax(np.random.random([20, 6]))
    ori_str, decode_str = ctc.greedy_decode(dist)
    logging.info("ori_str: {}".format(ori_str))
    logging.info("greed seach: {}".format(decode_str))

    beam = ctc.beam_decode(dist, beam_size=32)
    for string, score in beam[:20]:
        logging.info("beam search : {}, score: {}".format(ctc.remove_blank(string), score))
    
    beam = ctc.prefix_beam_decode(dist, beam_size=32)
    for string, score in beam[:20]:
        logging.info("prefix beam search: {}, score: {}".format(ctc.remove_blank(string), score))

if __name__ == '__main__':
    np.random.seed(1111)
    main()
