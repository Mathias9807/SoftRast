#include "g_ent_player.h"

#include "v_main.h"


void tick();
void render();
void destroy();

Entity* G_CreatePlayer() {
	Entity* p = calloc(sizeof(Entity), 1);
	p->x = 0;
	p->y = -5.0;

	p->tick = tick;
	p->render = render;
	p->destroy = destroy;

	return p;
}

void tick(Entity* p) {
	if (pressedButtons & IN_LEFT) p->x -= 12 * gameDelta;
	if (pressedButtons & IN_RIGHT) p->x += 12 * gameDelta;
}

void render(Entity* p) {
	float gray[][2] = {
		{-0.5, 0}, {0.5, 0}, {0, 1.5},
	};
	float blue[][2] = {
		{-0.25, 0.35}, {0.25, 0.35}, {0, 1.5},
	};
	float black[][2] = {
		{-0.1, 1}, {0.1, 1}, {0, 1.5},
	};

	V_DrawTriangles((float*) gray, 1, p->x, p->y, 0x44, 0x44, 0x44);
	V_DrawTriangles((float*) blue, 1, p->x, p->y, 0, 0, 0xAA);
	V_DrawTriangles((float*) black, 1, p->x, p->y, 0x11, 0x11, 0x11);
}

void destroy(Entity* p) {
	free(p);
}

