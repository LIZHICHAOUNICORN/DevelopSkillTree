import numpy as np
import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.DEBUG, format=FORMAT)


class ToyNN():
    def __init__(self, input_dim, output_dim):
        self.weight = np.random.random([input_dim, output_dim])
        # self.bias = np.random.random([output_dim])

    def softmax(self, logits):
        max_value = np.max(logits, axis=1, keepdims=True)
        exp = np.exp(logits - max_value)
        exp_sum = np.sum(exp, axis=1, keepdims=True)
        dist = exp/exp_sum
        return dist

    def forward(self, x):
        # x: T * m
        # self.weight: m * n
        logits = np.matmul(x, self.weight)
        # logits = np.matmul(x, self.weight) + self.bias
        dist = self.softmax(logits)

        return dist

def main():
    T, V = 12, 5
    m, n = 6, V
    
    x = np.random.random([T, m])
    nn = ToyNN(m, n)
    dist = nn.forward(x)
    logging.debug("dist: {}".format(dist))
    logging.info("dist dim sum: {}".format(dist.sum(1, keepdims=True)))

if __name__ == '__main__':
    np.random.seed(0)
    main()
