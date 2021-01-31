
# 使用pytorch进行分布式训练学习

## 内容简介

1. Setup
	1.1. 术语说明
2. 通信方式
	2.1. 点对点通信
	2.2. 集体通信
	2.2.1. 集体通信方式支持
	2.2.2. 集体通信操作支持
3. 分布式训练 hello world
4. 进阶
	4.1. 通信后端
5. Reference


### 01 Setup
  在分布式模型训练中，需要在集群间同步梯度，那么这时候需要考虑如何对pytorch使用。正好使用pytorch中distributed包可以帮助实现这个目的，
可以让科研人员或者实践人员很简单在集群之上使用pytorch，能够完成任何两个进程间通信，进程可以使用不同的通信后端。下面使用单机多个进程间进行实验。
  后续的修改都在这个版本上进行。在init_process中完成对进程的初始化。
```
"""run.py:"""
#!/usr/bin/env python
import os
import torch
import torch.distributed as dist
from torch.multiprocessing import Process
​
def run(rank, size):
    """ Distributed function to be implemented later. """
    pass
​
def init_process(rank, size, fn, backend='gloo'):
    """ Initialize the distributed environment. """
    os.environ['MASTER_ADDR'] = '127.0.0.1'
    os.environ['MASTER_PORT'] = '29500'
    dist.init_process_group(backend, rank=rank, world_size=size)
    fn(rank, size)
​
if __name__ == "__main__":
    size = 2
    processes = []
    for rank in range(size):
        p = Process(target=init_process, args=(rank, size, run))
        p.start()
        processes.append(p)
​
    for p in processes:
        p.join()
```

#### 1.1 术语说明：  
node: 节点，集群中服务器的个数。  
the number of GPUs per node:  节点对应的GPU卡数，即单机多卡是卡的总数。  
world_size: node * the number of GPUs per node . 进程组的总进程数。  
local world size：某个节点下进程数。  
rank: 进程组的索引。  

### 02 通信方式

#### 2.1 点对点通信

如下图，数据从一个进程到另外一个进程，这个操作被称为点对点通信。  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/send_recv.png)
因为点对点通信实现支持已经在pytorch 1.1中depressed了，下面可以看做是伪代码。  

```
"""Blocking point-to-point communication."""
​
def run(rank, size):
    tensor = torch.zeros(1)
    if rank == 0:
        tensor += 1
        # Send the tensor to process 1
        dist.send(tensor=tensor, dst=1)
    else:
        # Receive tensor from process 0
        dist.recv(tensor=tensor, src=0)
```

2.2 集体通信

相对于点对点通信，集体通信是对于进程组中所有进程的通信。进程组可以是所有进程的子集。使用dist.new_group()创建一个进程组，默认情况下，
集体操作的执行是对所有进程。例如，如果想要或者进程组中的tensor求和，那么可以使用dist.all_reduce()，如下面代码示例，具体代码参考原文链接中附代码：
```
""" All-Reduce example."""
def run(rank, size):
    """ Simple point-to-point communication. """
    group = dist.new_group([0, 1])
    tensor = torch.ones(1)
    dist.all_reduce(tensor, op=dist.reduce_op.SUM, group=group)
    print('Rank ', rank, ' has data ', tensor[0])   
```

代码运行结果图：
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/all_reduce_result.png)

#### 2.2.1 集体通信方式支持

有以下几类：
Scatter:  dist.scatter(tensor, src, scatter_list, group): 将scatter_list中第i个值拷贝到进程组中第i个进程的tensor变量中。  
gather：收集进程组中的变量值，只将结果复制到当前进程  
reduce：dist.reduce(tensor, dst, op, group): 将操作op在进程组中执行，把结果只放到执行的进程中的tensor变量。  
all-reduce：将操作op在进程组中执行，把结果放到所有进程中的tensor变量。  
broadcast：把变量分发给进程组中每个变量  
all-gather：收集进程组中的变量值，将结果复制到进程组的每个进程。  

图3 Scatter  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/scatter.png)  
图4 Gather  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/gather.png)  
图5 Reduce  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/reduce.png)  
图6 All-Reduce  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/all_reduce.png)  
图7 Broadcast  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/broadcast.png)  
图8 All-Gather  
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/all_gather.png)  
#### 2.2.1 集体通信操作支持

dist.reduce_op.SUM： 求和  
dist.reduce_op.PRODUCT：求乘积  
dist.reduce_op.MAX：求最大值  
dist.reduce_op.MIN：求最小值  

### 03 分布式训练 hello world

数据集分割：  
```
""" Dataset partitioning helper """
class Partition(object):
​
    def __init__(self, data, index):
        self.data = data
        self.index = index
​
    def __len__(self):
        return len(self.index)
​
    def __getitem__(self, index):
        data_idx = self.index[index]
        return self.data[data_idx]
​
​
class DataPartitioner(object):
​
    def __init__(self, data, sizes=[0.7, 0.2, 0.1], seed=1234):
        self.data = data
        self.partitions = []
        rng = Random()
        rng.seed(seed)
        data_len = len(data)
        indexes = [x for x in range(0, data_len)]
        rng.shuffle(indexes)
​
        for frac in sizes:
            part_len = int(frac * data_len)
            self.partitions.append(indexes[0:part_len])
            indexes = indexes[part_len:]
​
    def use(self, partition):
        return Partition(self.data, self.partitions[partition])
```
对mnist数据集进行分割  
```
""" Partitioning MNIST """
def partition_dataset():
    dataset = datasets.MNIST('./data', train=True, download=True,
                             transform=transforms.Compose([
                                 transforms.ToTensor(),
                                 transforms.Normalize((0.1307,), (0.3081,))
                             ]))
    size = dist.get_world_size()
    bsz = 128 / float(size)
    partition_sizes = [1.0 / size for _ in range(size)]
    partition = DataPartitioner(dataset, partition_sizes)
    partition = partition.use(dist.get_rank())
    train_set = torch.utils.data.DataLoader(partition,
                                         batch_size=bsz,
                                         shuffle=True)
    return train_set, bsz
```
使用异步sgd作为optimizer  
```
""" Distributed Synchronous SGD Example """
def run(rank, size):
    torch.manual_seed(1234)
    train_set, bsz = partition_dataset()
    model = Net()
    optimizer = optim.SGD(model.parameters(),
                          lr=0.01, momentum=0.5)
​
    num_batches = ceil(len(train_set.dataset) / float(bsz))
    for epoch in range(10):
        epoch_loss = 0.0
        for data, target in train_set:
            optimizer.zero_grad()
            output = model(data)
            loss = F.nll_loss(output, target)
            epoch_loss += loss.item()
            loss.backward()
            average_gradients(model)
            optimizer.step()
        print('Rank ', dist.get_rank(), ', epoch ',
              epoch, ': ', epoch_loss / num_batches)
```
在训练过程中对梯度进行平均。  
```
""" Gradient averaging. """
def average_gradients(model):
    size = float(dist.get_world_size())
    for param in model.parameters():
        dist.all_reduce(param.grad.data, op=dist.reduce_op.SUM)
        param.grad.data /= size
```

效果图示意：

### 04 进阶

#### 4.1 通信后端
通信后端有三种
1. gloo
2. mpi
3. nccl
下面是他们对device支持以及通信方式的支持对比。
![](https://github.com/LIZHICHAOUNICORN/MachineLearningWorkflow/blob/main/pytorch_distributed/pic/backend.png)  
 
### 05 Reference
https://pytorch.org/tutorials/intermediate/dist_tuto.html
https://github.com/pytorch/tutorials/issues/657
