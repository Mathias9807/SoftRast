#ifndef __G_ENT_BULLET_H__
#define __G_ENT_BULLET_H__


#include "g_main.h"


typedef struct {
	Entity e;

	float* polys;
	int numPolys;
	float col[3];

	float vx;
	float vy;

	float damage;
	Entity* parent;
} BulletEntity;

Entity* G_CreateBullet(float x, float y, float* polys, int numPolys, float r, float g, float b, float vx, float vy, float damage, Entity* parent);


#endif

