CC = gcc
CFLAGS = -O3 -Wall -g -Wno-unused-function -Wno-deprecated-declarations
LDLIBS = -lm

ifeq ($(shell uname -s), Darwin)
   LDLIBS += -framework OpenGL -framework GLUT
else
   LDLIBS += -lglut -lGLU -lGL
endif

LDLIBS += $(shell sdl2-config --libs)
LDFLAGS += $(shell sdl2-config --cflags)

tsp_src := $(wildcard tsp_*.c matching.c)
tsp_obj := $(patsubst %.c,%.o,$(tsp_src))

tsp_main:  tools.o $(tsp_obj)

.PHONY: clean
clean:
	rm -f *.o
	rm -f tsp_main
	rm -f matching
	rm -fr *.dSYM/
