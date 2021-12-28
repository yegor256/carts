
SRCS = $(wildcard *.cpp)
OBJS = $(addprefix bin/,${SRCS:.cpp=.o})
BINS = $(OBJS:.o=.a)

CPPFLAGS = -Wall -std=c++11
LDLIBS = -lstdc++ -lm

all: $(BINS)

bin/%.o: %.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -c -o "$@" "$<"

%.cpp:

bin/%.a: bin/%.o
	mkdir -p bin
	cc "$<" $(LDLIBS) -o "$@"

.PHONY: clean
clean:
	rm -rf bin