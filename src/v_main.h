#ifndef __V_MAIN_H__
#define __V_MAIN_H__


#include <math.h>

#include <SDL/SDL.h>

#define WIDTH 640
#define HEIGHT 480


extern SDL_Surface* window;

void V_Init();
void V_Tick();
void V_SetPixel(int x, int y, int r, int g, int b);
void V_Quit();

void V_RasterizeTriangle(float v[3][2], char r, char g, char b);

float xToScr(float x);
float yToScr(float y);


#endif

