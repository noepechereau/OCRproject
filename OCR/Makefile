# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=  -MMD
CFLAGS= `pkg-config --cflags sdl2 SDL2_image` -Wall -Wextra -O3
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl2 SDL2_image`

all: main
main: main.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

-include main.d

# END
