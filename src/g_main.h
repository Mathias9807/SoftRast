#ifndef __G_MAIN_H__
#define __G_MAIN_H__


#include "def.h"

#include "v_main.h"
#include "g_collider.h"


#define IN_UP		(1 << 0)
#define IN_DOWN		(1 << 1)
#define IN_RIGHT	(1 << 2)
#define IN_LEFT		(1 << 3)
#define IN_A		(1 << 4)
#define IN_B		(1 << 5)

extern int heldButtons;
extern int pressedButtons;
extern float gameDelta;
extern float gameClock;

typedef enum {
	ENT_NULL = 0,
	ENT_PLAYER,
	ENT_LINEAR,
	ENT_BULLET,
	ENT_RAY
} EntType;

typedef struct EntityStruct {
	EntType type;
	ColliderShape collider;

	float x;
	float y;
	float size;
	bool dying;

	void (*tick)(struct EntityStruct*);
	void (*collision)(struct EntityStruct*, struct EntityStruct*);
	void (*render)(struct EntityStruct*);
	void (*destroy)(struct EntityStruct*);
} Entity;

extern List g_entities;

void G_Init();
void G_Tick();
void G_EntityTick(Entity* e);
void G_EntityCollision(Entity* a, Entity* b);
void G_EntityRender(Entity* e);
void G_EntityDestroy(Entity* e);
void G_Quit();


#endif

