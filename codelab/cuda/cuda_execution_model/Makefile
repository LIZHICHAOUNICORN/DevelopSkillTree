CU_APPS=simpleDiveragence

all: ${CU_APPS}

%: %.cu
	nvcc -O2 -arch=sm_60 -o $@ $<

clean:
	rm -f ${CU_APPS}
