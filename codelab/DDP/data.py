from __future__ import print_function
import argparse
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
from torch.optim.lr_scheduler import StepLR
from torch.nn.parallel import DistributedDataParallel as DDP


def init_dataset(args):
    train_kwargs = {'batch_size': 1}
    test_kwargs = {'batch_size': 1}
    cuda_kwargs = {'num_workers': 1,
                   'pin_memory': True,
                   'shuffle': False}
    train_kwargs.update(cuda_kwargs)
    test_kwargs.update(cuda_kwargs)

    transform=transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
        ])
    dataset1 = datasets.MNIST('../data', train=True, download=True,
                       transform=transform)
    # dataset2 = datasets.MNIST('../data', train=False,
    #                   transform=transform)
    # train_loader = torch.utils.data.DataLoader(dataset1,**train_kwargs)
    train_sampler = torch.utils.data.distributed.DistributedSampler(dataset1,num_replicas=args.world_size, rank=args.rank, shuffle=False, seed=42)
    train_loader = torch.utils.data.DataLoader(dataset1, sampler=train_sampler, batch_size=8, shuffle=False, num_workers=4, pin_memory=True)
    # test_loader = torch.utils.data.DataLoader(dataset2, **test_kwargs)
    # test_loader = torch.utils.data.distributed.DistributedSampler(dataset2, **test_kwargs)
    return train_loader

