#ifndef __G_ENT_RAY_H__
#define __G_ENT_RAY_H__


#include "g_main.h"


typedef struct {
	Entity e;

	float spawnTime;

	float col[3];

	float vx;
	float vy;

	float damage;
	Entity* parent;
} RayEntity;

Entity* G_CreateRay(float r, float g, float b, float damage, Entity* parent);


#endif

