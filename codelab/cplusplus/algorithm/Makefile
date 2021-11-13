APPS=algorithm_function_upper_bound

all: ${APPS}

%: %.cc
	g++ --std=c++11 -fno-elide-constructors -o $@ $<
clean:
	rm -f ${APPS}
