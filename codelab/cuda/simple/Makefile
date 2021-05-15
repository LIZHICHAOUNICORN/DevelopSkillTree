APPS=hello

all: ${APPS}

%: %.cu
	nvcc -O2 -arch=sm_60 -o $@ $<
clean:
	rm -f ${APPS}
