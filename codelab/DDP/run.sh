#!/bin/bash

# Use this to control how many gpu you use, It's 1-gpu training if you specify
# just 1gpu, otherwise it's is multiple gpu training based on DDP in pytorch
export CUDA_VISIBLE_DEVICES="0,1,2,3,4,5,6,7"
# export NCCL_DEBUG=INFO
# export NCCL_P2P_DISABLE=1
# export NCCL_IB_DISABLE=1
# export NCCL_SOCKET_IFNAME=bond0

# export CUDA_VISIBLE_DEVICES="5,6,7,8"
# The num of nodes
rank=$1

num_nodes=2
# The rank of current node
node_rank=$rank

train_config=config.yaml

dir=$PWD/training
max_epoch=3
stage=1

set -u
set -o pipefail

echo "Start training"
mkdir -p $dir
# INIT_FILE is for DDP synchronization
INIT_FILE=$dir/ddp_init
init_method=file://$(readlink -f $INIT_FILE)

echo "$0: init method is $init_method"

num_gpus=$(echo $CUDA_VISIBLE_DEVICES | awk -F "," '{print NF}')
# Use "nccl" if it works, otherwise use "gloo"
dist_backend="nccl"
world_size=`expr $num_gpus \* $num_nodes`
echo "total gpus is: $world_size"

if [ $stage -le 2 ]; then
    for ((i = 0; i < $num_gpus; ++i)); do
    {
      gpu_id=$(echo $CUDA_VISIBLE_DEVICES | cut -d',' -f$[$i+1])
      # Rank of each gpu/process used for knowing whether it is
      # the master of a worker.
      rank=`expr $node_rank \* $num_gpus + $i`
      python train.py \
        --config $train_config \
        --epoch $max_epoch \
        --ddp.init_method $init_method \
        --ddp.world_size $world_size \
        --ddp.rank $rank \
        --ddp.dist_backend $dist_backend 
    } &
    done
    wait
fi 
