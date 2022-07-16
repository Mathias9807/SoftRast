#include "g_ent_bullet.h"

#include "g_collider.h"
#include "v_main.h"


static void tick();
static void collision();
static void render();
static void destroy();

Entity* G_CreateBullet(float x, float y, float* polys, int numPolys, float r, float g, float b, float vx, float vy, float damage, Entity* parent) {
	BulletEntity* bullet = calloc(sizeof(BulletEntity), 1);
	bullet->e.type = ENT_BULLET;
	bullet->e.x = x;
	bullet->e.y = y;
	bullet->e.size = 0.1;
	bullet->polys = polys;
	bullet->numPolys = numPolys;
	bullet->col[0] = r;
	bullet->col[1] = g;
	bullet->col[2] = b;
	bullet->vx = vx;
	bullet->vy = vy;
	bullet->damage = damage;
	bullet->parent = parent;

	bullet->e.tick = tick;
	bullet->e.render = render;
	bullet->e.collision = collision;

	ListAdd(&g_colliders, bullet);

	return (Entity*) bullet;
}

static void tick(Entity* e) {
	BulletEntity* b = (BulletEntity*) e;
	b->e.x += b->vx * gameDelta;
	b->e.y += b->vy * gameDelta;
}

static void collision(Entity* this, Entity* c) {
	if (((BulletEntity*) this)->parent == c) return;

	this->dying = true;
}

static void render(Entity* e) {
	BulletEntity* b = (BulletEntity*) e;
	V_DrawTriangles(b->polys, b->numPolys, b->e.x, b->e.y, b->col[0], b->col[1], b->col[2]);
}

static void destroy(Entity* this) {
	int i = ListFind(&g_colliders, this);
	ListRemove(&g_colliders, i);

	i = ListFind(&g_entities, this);
	ListRemove(&g_entities, i);

	free(this);
}

