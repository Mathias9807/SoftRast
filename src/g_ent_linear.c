#include "g_ent_linear.h"
#include "g_ent_bullet.h"

#include "g_collider.h"
#include "v_main.h"


static void tick(Entity*);
static void collision(Entity* this, Entity* c);
static void render(Entity*);
static void destroy(Entity*);

static float bullet[] = {
	0.2, 0, 0, 0.2, -0.2, 0,
	0.2, 0, 0, -0.2, -0.2, 0,
};

Entity* G_CreateLinear(float x, float y, float vx, float vy) {
	LinearEntity* l = calloc(sizeof(LinearEntity), 1);
	l->e.type = ENT_LINEAR;
	l->e.x = x;
	l->e.y = y;
	l->e.size = 0.2;
	l->vx = vx;
	l->vy = vy;

	l->e.tick = tick;
	l->e.collision = collision;
	l->e.render = render;

	ListAdd(&g_colliders, l);

	return (Entity*) l;
}

static void tick(Entity* this) {
	LinearEntity* l = (LinearEntity*) this;
	l->e.x += l->vx * gameDelta;
	l->e.y += l->vy * gameDelta;

	if (gameClock - l->lastFiredTime > 1) {
		ListAdd(&g_entities, G_CreateBullet(this->x, this->y, bullet, 2, 0xEE, 0x22, 0x22, 0, -20, 10, this));
		l->lastFiredTime = gameClock;
	}
}

static void collision(Entity* this, Entity* c) {
	if (c->type == ENT_BULLET && ((BulletEntity*) c)->parent == this) return;

	this->dying = true;
}

static void render(Entity* this) {
	float green[][2] = {
		{-0.4, 0}, {0.4, 0}, {0, -1},
	};

	V_DrawTriangles((float*) green, 1, this->x, this->y, 0x33, 0xAA, 0x44);
}

