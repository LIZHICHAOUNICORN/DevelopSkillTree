CU_APPS=simpleDiveragence simpleDeviceQuery sumMatrix reduceinteger

all: ${CU_APPS}

%: %.cu
	nvcc -O2 -arch=sm_60 -o $@ $<

clean:
	rm -f ${CU_APPS}
