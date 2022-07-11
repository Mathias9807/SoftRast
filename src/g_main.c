#include "g_main.h"
#include "g_ent_player.h"


List g_entities;

Entity* player;

void G_Init() {
	ListAdd(&g_entities, player = G_CreatePlayer());
}

void G_Tick() {
	for (ListEntry* e = g_entities.first; e; e = e->next)
		G_EntityTick((Entity*) e->value);
}

void G_EntityTick(Entity* e) {
	if (e->tick) e->tick(e);
}

void G_EntityRender(Entity* e) {
	if (e->render) e->render(e);
}

void G_Quit() {
}

