#ifndef __G_MAIN_H__
#define __G_MAIN_H__


#include <math.h>

#include "v_main.h"


#define IN_UP		(1 << 0)
#define IN_DOWN		(1 << 1)
#define IN_RIGHT	(1 << 2)
#define IN_LEFT		(1 << 3)
#define IN_A		(1 << 4)
#define IN_B		(1 << 5)

extern int pressedButtons;
extern float gameDelta;


void G_Init();
void G_Tick();
void G_Quit();


#endif

