#ifndef __V_MAIN_H__
#define __V_MAIN_H__


#include <math.h>

#include <SDL/SDL.h>

#define WIDTH 640
#define HEIGHT 480


extern SDL_Surface* window;

extern float V_viewOffs[2];
extern float V_viewScale[2];

void V_Init();
void V_Tick();
void V_SetPixel(int x, int y, int r, int g, int b);
void V_SetRow(int y, int r, int g, int b);
void V_ClearScreen(int r, int g, int b);
void V_Quit();

void V_DrawTriangles(float* v, size_t n, float x, float y, char r, char g, char b);
void V_RasterizeTriangle(float v[3][2], char r, char g, char b);

float xToScr(float x);
float yToScr(float y);


#endif

