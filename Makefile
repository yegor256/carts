CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
OUT = objects

CPPFLAGS = -Wall -std=c++11
LDLIBS = -lstdc++ -lm

all: binaries

binaries: $(OBJFILES)
	cc objects.o $(LDLIBS) -o objects

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
