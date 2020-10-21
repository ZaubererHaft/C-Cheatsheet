# Warning flags
# For more information about gcc warnings: https://embeddedartistry.com/blog/2017/3/7/clang-weverything
# -Wall:		        Print warnings
# -Wextra:		        Enable additional warnings not covered by "-Wall"
# -Wpedantic:	        Reject everything that is not ISO C
# -g					Generates debug information to be used by GDB debugger
WFLAGS = -Wall -Wextra -Wpedantic -g

all:
	mkdir -p bin
	gcc main.c $(WFLAGS) -o bin/program.out

run:
	bin/program.out