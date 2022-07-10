#include "g_main.h"


void G_Init() {
}

void G_Tick() {
	if (pressedButtons & IN_UP) V_viewOffs[1] -= 8 * gameDelta;
	if (pressedButtons & IN_DOWN) V_viewOffs[1] += 8 * gameDelta;
	if (pressedButtons & IN_LEFT) V_viewOffs[0] += 8 * gameDelta;
	if (pressedButtons & IN_RIGHT) V_viewOffs[0] -= 8 * gameDelta;
}

void G_Quit() {
}

