SRCS = $(wildcard *.c*)
OBJS = $(addprefix bin/,${SRCS:.c*=.o})
BINS = $(OBJS:.o=.a)

CPPFLAGS = -Wall -std=c++11
LDLIBS = -lstdc++ -lm

all: $(BINS)

bin/%.o: %.c*
	mkdir -p bin
	g++ $(CPPFLAGS) -c -o "$@" "$<"

%.c*:

bin/%.a: bin/%.o
	mkdir -p bin
	cc "$<" $(LDLIBS) -o "$@"

.PHONY: clean
clean:
	rm -rf bin
