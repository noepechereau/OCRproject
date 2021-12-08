# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=`pkg-config --cflags gtk+-3.0`  $(shell pkg-config --cflags SDL2_image) -MMD
CFLAGS= -Wall -Wextra -rdynamic -std=c99  -O3 -DNO_INLINE -fsanitize=address -lm -g 
LDFLAGS=`pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS= `pkg-config --libs gtk+-3.0`   $(shell pkg-config --libs SDL2_image) $(shell sdl2-config --cflags --libs) -ldl

PROG = ocr_glade
SRC= ../image_system/image_manipulation.c ../image_system/color_system.c ../image_system/image_system.c ../useful/basics.c ../rotation/rotation.c ocr_glade.c 

OBJ=${SRC:.c=.o}

all: ${OBJ}
	${CC} ${CFLAGS} $^ -o ocr ${LDLIBS}

clean:
	${RM} *.o
	${RM} /.o
	${RM} *.d
	${RM} ocr
	${RM} *.bmp

# END
