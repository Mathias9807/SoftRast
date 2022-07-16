#include "g_collider.h"


List g_colliders;

void G_TickCollision() {
	for (ListEntry* e = g_colliders.first; e; e = e->next) {
		Entity* a = (Entity*) e->value;

		for (ListEntry* f = g_colliders.first; f; f = f->next) {
			if (e == f) continue;

			Entity* b = (Entity*) f->value;

			float dX = b->x - a->x;
			float dY = b->y - a->y;
			if (dX * dX + dY * dY <= (a->size + b->size) * (a->size + b->size)) {
				G_EntityCollision(a, b);
				G_EntityCollision(b, a);
			}
		}
	}
}

void G_EntityCollision(Entity* a, Entity* b) {
	if (a->collision) a->collision(a, b);
}

