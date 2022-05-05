export CUDA_VISIBLE_DEVICES="0, 2"

python train.py --config config.yaml \
	--epoch 3 \
	--ddp.init_method file:///mnt/nfs/ptm10/zhichaoli/workspace/SimpleDDP/toy/training/ddp_init \
	--ddp.world_size 2 \
	--ddp.rank 0 \
	--ddp.dist_backend nccl
