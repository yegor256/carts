CPPFILES = $(wildcard *.c)
OBJFILES = $(CPPFILES:.c=.o)
OUT = functions

CPPFLAGS = -Wall -fsanitize=address
LDLIBS = -stdlibc -lm -static-libasan

all: binaries

binaries: $(OBJFILES)
	cc functions.o $(LDLIBS) -o functions

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
