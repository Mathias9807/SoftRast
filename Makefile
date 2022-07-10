OUT=softrast

SOURCES=src/main.c src/v_main.c src/v_rasterizer.c src/g_main.c

INCLUDES=-I./include -I./src

OTHER=`sdl-config --cflags --libs` -lm

all:
	gcc ${INCLUDES} ${OTHER} ${SOURCES} -o ${OUT} -std=gnu11 -g

