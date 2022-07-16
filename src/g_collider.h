#ifndef __G_COLLIDER_H__
#define __G_COLLIDER_H__


#include "def.h"
#include "g_main.h"


extern List g_colliders;

void G_TickCollision();
void G_EntityCollision(Entity* a, Entity* b);


#endif

