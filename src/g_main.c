#include "g_main.h"
#include "g_collider.h"
#include "g_ent_player.h"
#include "g_ent_linear.h"


List g_entities;

Entity* player;

void G_Init() {
	ListAdd(&g_entities, player = G_CreatePlayer());
}

void G_Tick() {
	// Tick each entity
	for (ListEntry* e = g_entities.first; e; e = e->next)
		G_EntityTick((Entity*) e->value);

	// Check and handle collision
	G_TickCollision();

	// Delete all dead entities
	ListEntry* cur = g_entities.first;
	while (cur) {
		Entity* e = cur->value;
		if (e->dying) {
			printf("Deleting dead entity\n");
			cur = cur->next;
			G_EntityDestroy(e);
			continue;
		}
		cur = cur->next;
	}

	// Spawn enemies every 5s
	static int lastSpawn = 0;
	if (gameClock - lastSpawn > 5) {
		printf("Spawning enemies\n");

		float speed = 5;
		float x = (float) rand() / RAND_MAX * 20 - 10;
		float y = 10;
		float len = sqrt(x * x + y * y);
		float spacing = 1;
		ListAdd(&g_entities, G_CreateLinear(x, y - spacing, -x / len * speed, -y / len * speed));
		ListAdd(&g_entities, G_CreateLinear(x + spacing, y, -x / len * speed, -y / len * speed));
		ListAdd(&g_entities, G_CreateLinear(x - spacing, y, -x / len * speed, -y / len * speed));
		lastSpawn = (int) gameClock;
	}
}

void G_EntityTick(Entity* e) {
	if (e->tick) e->tick(e);
}

void G_EntityRender(Entity* e) {
	if (e->render) e->render(e);
}

void G_EntityDestroy(Entity* e) {
	printf("Destroying entity %d\n", e->type);

	if (e->destroy) e->destroy(e);

	int i = ListFind(&g_colliders, e);
	if (i >= 0) ListRemove(&g_colliders, i);

	i = ListFind(&g_entities, e);
	if (i >= 0) ListRemove(&g_entities, i);

	free(e);
}

void G_Quit() {
}

