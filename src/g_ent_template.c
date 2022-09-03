#include "g_ent_¤.h"

#include "g_collider.h"


static void tick();
static void collision();
static void render();

Entity* G_Create¤(float x, float y) {
	¤Entity* e = calloc(sizeof(¤Entity), 1);
	e->e.type = ENT_¤;
	e->e.x = x;
	e->e.y = y;
	e->e.size = 0.1;

	e->e.tick = tick;
	e->e.render = render;
	e->e.collision = collision;

	ListAdd(&g_colliders, e);

	return (Entity*) e;
}

static void tick(Entity* e) {
}

static void collision(Entity* this, Entity* c) {
	if (c->type == ENT_BULLET) {
	       if (((BulletEntity*) c)->parent == this) return;

		this->dying = true;
	}
}

static void render(Entity* e) {
}

