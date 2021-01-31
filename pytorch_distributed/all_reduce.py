#!/usr/bin/env python
import os
import torch
import torch.distributed as dist
from torch.multiprocessing import Process

from config import logger
from config import set_global_variables
from config import get_args

def run(rank, size):
    """ Distributed function to be implemented later. """
    logger.info("{} start run".format(rank))
    t = torch.rand(2, 2)
    logger.info("rank: {} t: {}".format(rank, t))
    t = t.cuda()
    for _ in range(1):
        c = t.clone()
        dist.all_reduce(c, dist.ReduceOp.SUM)
        t.set_(c)
    logger.info("{} value: {}".format(rank, t))


def init_processes(rank, size, fn, backend='nccl'):
    """ Initialize the distributed environment. """
    os.environ['MASTER_ADDR'] = '127.0.0.1'
    os.environ['MASTER_PORT'] = '29500'
    dist.init_process_group(backend, rank=rank, world_size=size)
    fn(rank, size)

def start(size):
    processes = []
    for rank in range(size):
        p = Process(target=init_processes, args=(rank, size, run))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()

if __name__ == "__main__":
    set_global_variables()
    args = get_args()
    logger.info("args: {}".format(args))
    start(args.size)
