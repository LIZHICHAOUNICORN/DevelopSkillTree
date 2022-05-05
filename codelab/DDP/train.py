import argparse
import logging
import yaml

import torch
import torch.distributed as dist
import torch.optim as optim
from torch.optim.lr_scheduler import StepLR
import torch.nn.functional as F
from torch.nn.parallel import DistributedDataParallel as DDP

from model import init_model
from data import init_dataset


torch.backends.cudnn.deterministic = True
torch.backends.cudnn.benchmark = False

def get_args():
    parser = argparse.ArgumentParser(description="training network")
    parser.add_argument("--config", required=True, help="config file")
    parser.add_argument("--epoch", default=3, type=int, dest="epoch", help="training max epoch")
    parser.add_argument("--log_interval", default=100, type=int, dest="log_interval", help="log print interval")
    parser.add_argument("--ddp.rank", default=0, type=int, dest="rank", help="global rank for distributed training")
    parser.add_argument("--ddp.world_size", default=-1, type=int, dest="world_size", help="global rank for distributed training")
    parser.add_argument("--ddp.dist_backend", default="nccl", choices=["nccl", "gloo"], dest="dist_backend", help="distributed backend")
    parser.add_argument("--ddp.init_method", default=None, dest="init_method", help="distributed init method")
    args = parser.parse_args()
    return args

class Executor:
    def __init__(self):
        self.step = 0
    def train(self, model, optimizer, scheduler, data_loader, epoch, args, device=torch.device("cuda")):
        model.train()
        model_context = model.join
        with model_context():
            for batch_idx, (data, target) in enumerate(data_loader):
                data, target = data.to(device), target.to(device)
                optimizer.zero_grad()
                output = model(data)
                loss = F.nll_loss(output, target)
                loss.backward()
                optimizer.step()
                if batch_idx % args.log_interval == 0:
                    logging.info("rank: {} train epoch {}, [{}] loss {}".format(args.rank, epoch, batch_idx * len(data), loss.item()))
                self.step += 1
                scheduler.step()



def main():
    args = get_args()
    logging.basicConfig(level=logging.DEBUG,
                        format='%(filename)s %(levelname)s %(lineno)d %(message)s')

    torch.manual_seed(777)
    with open(args.config, 'r') as fin:
        configs = yaml.load(fin, Loader=yaml.FullLoader)

    model = init_model()
    logging.debug("the number of params: {}".format(sum(p.numel() for p in model.parameters())))
    logging.info("args: {}".format(args))
    local_rank = args.rank
    if args.rank >= 8:
        local_rank = args.rank % 8

    dist.init_process_group(args.dist_backend, init_method=args.init_method,
                            world_size=args.world_size,
                            rank=args.rank)
    model.cuda(local_rank)
    model = torch.nn.parallel.DistributedDataParallel(model, device_ids=[local_rank])

    # device = torch.device("cuda:{}".format(args.rank))
    device = torch.device("cuda:{}".format(local_rank))
    model.to(device)
    logging.info("device: {}".format(device))

    optimizer = optim.Adam(model.parameters(), **configs["optim_conf"])
    scheduler = StepLR(optimizer, step_size=1, gamma=0.7)
    train_data_loader = init_dataset(args)
    executor = Executor()


    for epoch in range(0, args.epoch):
        executor.train(model, optimizer, scheduler, train_data_loader, epoch, args, device=device)

    

if __name__ == '__main__':
    main()
