APPS=move_constructor copy_constructor move_constructor2

all: ${APPS}

%: %.cc
	g++ --std=c++11 -fno-elide-constructors -o $@ $<
clean:
	rm -f ${APPS}
