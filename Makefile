CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
OUT = main

CPPFLAGS = -Wall -std=c++11
LDLIBS = -lstdc++ -lm

$(OUT): $(OBJFILES)

all: $(OUT)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
