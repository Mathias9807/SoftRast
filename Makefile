OUT=softrast

SOURCES=src/def.c src/main.c src/v_main.c src/v_rasterizer.c src/g_main.c src/g_ent_player.c

INCLUDES=-I./include -I./src

OTHER=`sdl-config --cflags --libs` -lm

all:
	gcc ${INCLUDES} ${OTHER} ${SOURCES} -o ${OUT} -std=gnu11 -g

