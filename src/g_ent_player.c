#include "g_ent_player.h"

#include "g_ent_bullet.h"
#include "g_ent_ray.h"
#include "g_collider.h"
#include "v_main.h"


static float bullet[] = {
	0.2, 0, 0, 0.2, -0.2, 0,
	0.2, 0, 0, -0.2, -0.2, 0,
};

static void tick();
static void render();
static void collision();

Entity* G_CreatePlayer() {
	Entity* p = calloc(sizeof(Entity), 1);
	p->type = ENT_PLAYER;
	p->x = 0;
	p->y = -5.0;
	p->size = 0.5;

	p->tick = tick;
	p->render = render;
	p->collision = collision;

	ListAdd(&g_colliders, p);

	return p;
}

static void tick(Entity* p) {
	if (heldButtons & IN_LEFT) p->x -= 12 * gameDelta;
	if (heldButtons & IN_RIGHT) p->x += 12 * gameDelta;

	if (pressedButtons & IN_A) ListAdd(&g_entities, G_CreateBullet(p->x, p->y, bullet, 2, 0xEE, 0xEE, 0x22, 0, 20, 10, p));
	if (pressedButtons & IN_B) ListAdd(&g_entities, G_CreateRay(0xEE, 0xEE, 0x22, 10, p));
}

static void collision(Entity* this, Entity* c) {
	if (c->type == ENT_BULLET && ((BulletEntity*) c)->parent == this) return;

	this->dying = true;
}

static void render(Entity* p) {
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

