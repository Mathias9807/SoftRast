#ifndef __G_COLLIDER_H__
#define __G_COLLIDER_H__


#include "def.h"


typedef enum {
	C_NONE = 0,
	C_CIRCLE,
	C_SQUARE
} ColliderShapeEnum;

typedef struct {
	ColliderShapeEnum type;
	float a;
	float b;
} ColliderShape;

extern List g_colliders;

void G_TickCollision();


#endif

