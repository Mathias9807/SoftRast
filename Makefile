INCLUDES=-I./include

OTHER=`sdl-config --cflags --libs` -lm

all:
	gcc ${INCLUDES} ${OTHER} src/main.c -o softrast -std=gnu11 -g

