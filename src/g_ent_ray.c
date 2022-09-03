#include "g_ent_ray.h"

#include "def.h"
#include "g_collider.h"
#include "v_main.h"


static void tick();
static void collision();
static void render();

static float triangle[] = {
	0, 0, -1, 0, -1, 1
};

#define START_TIME 0.5

Entity* G_CreateRay(float r, float g, float b, float damage, Entity* parent) {
	RayEntity* ray = calloc(sizeof(RayEntity), 1);
	ray->e.type = ENT_RAY;
	ray->e.x = parent->x;
	ray->e.y = parent->y;
	ray->e.size = 0.1;
	ray->spawnTime = gameClock;
	ray->col[0] = r;
	ray->col[1] = g;
	ray->col[2] = b;
	ray->damage = damage;
	ray->parent = parent;

	ray->e.tick = tick;
	ray->e.render = render;

	return (Entity*) ray;
}

static void tick(Entity* e) {
	RayEntity* r = (RayEntity*) e;
	r->e.x = r->parent->x;
	r->e.y = r->parent->y;

	if (!e->collision && gameClock - r->spawnTime > START_TIME) {
		ListAdd(&g_colliders, e);
		e->collision = collision;
	}
}

static void collision(Entity* this, Entity* c) {
	if (((RayEntity*) this)->parent == c) return;

	this->dying = true;
}

static void render(Entity* e) {
	RayEntity* r = (RayEntity*) e;
	float t = gameClock - r->spawnTime;

	float sy = 5.0;
	float radius = 0.5 - t / START_TIME * 0.5;
	if (radius <= 0) {
		radius = 0.3 + 0.1 * sin(t / 0.2 * 2 * M_PI);
		sy = 20.0;
	}

	float x = r->e.x + radius * cos(t / 0.5 * 2 * M_PI);
	float y = r->e.y;
	float sx = 1.0 * radius * sin(t / 0.5 * 2 * M_PI);
	V_DrawTrianglesScaled(triangle, 1, x, y, r->col[0], r->col[1], r->col[2], sx, sy);

	float x2 = r->e.x + radius * -cos(t / 0.5 * 2 * M_PI);
	float sx2 = 1.0 * radius * -sin(t / 0.5 * 2 * M_PI);
	V_DrawTrianglesScaled(triangle, 1, x2, y, r->col[0], r->col[1], r->col[2], sx2, sy);
}

