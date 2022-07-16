#ifndef __G_ENT_LINEAR_H__
#define __G_ENT_LINEAR_H__


#include "g_main.h"


typedef struct {
	Entity e;

	float vx;
	float vy;

	float lastFiredTime;
} LinearEntity;

Entity* G_CreateLinear(float x, float y, float vx, float vy);


#endif

