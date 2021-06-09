CU_APPS=checkDeviceInfo checkDimension sumArraysOnGpu_small_case sumArraysOnGpu_timer checkThreadIndex sumMatrixOnGpu_1D_grid_1D_block

all: ${CU_APPS}

%: %.cu
	nvcc -O2 -arch=sm_60 -o $@ $<

clean:
	rm -f ${CU_APPS}
