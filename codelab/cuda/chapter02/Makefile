CU_APPS=checkDeviceInfo checkDimension sumArraysOnGpu_small_case sumArraysOnGpu_timer

all: ${CU_APPS}

%: %.cu
	nvcc -O2 -arch=sm_60 -o $@ $<

clean:
	rm -f ${CU_APPS}
