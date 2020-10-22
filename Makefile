# Warning flags
# For more information about gcc warnings: https://embeddedartistry.com/blog/2017/3/7/clang-weverything
# -Wall:		        Print warnings
# -Wextra:		        Enable additional warnings not covered by "-Wall"
# -Wpedantic:	        Reject everything that is not ISO C
# -g					Generates debug information to be used by GDB debugger
# -03					Maximum optimization level
CC      := gcc
INPUT	:= main.c addparams.S
CFLAGS  := -g -O3
WFLAGS	:= -Wall -Wextra -Wpedantic -g

all:
	mkdir -p bin
	$(CC) $(INPUT) $(CFLAGS) $(WFLAGS) -o bin/program.out

clean:
	rm -rf bin

run:
	bin/program.out