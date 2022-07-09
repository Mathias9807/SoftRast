#include "v_main.h"


SDL_Surface* window;


void V_Init() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("SDL1.2 Software Rasterizer 今回は行ける気がする！", NULL);
	window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
}

void V_Tick() {
	float v[][2] = {
		{-0.5, 0}, {0.5, -0.5}, {0, 0.5},

		{-0.5, 0}, {-0.5, 0.5}, {0, 0.5},
		{-0.5, 0}, {0.5, -0.5}, {-0.5, -0.5},
		{0.5, 0.5}, {0.5, -0.5}, {0, 0.5},
	};

	for (int i = 0; i < sizeof(v) / sizeof(float[3][2]); i++)
		V_RasterizeTriangle(v + 3 * i, 0xAA, 0x44 + 0x20*i, 0x88 + 0x10*i);

}

void V_SetPixel(int x, int y, int r, int g, int b) {
	((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
		(r << window->format->Rshift) & window->format->Rmask
		| (g << window->format->Gshift) & window->format->Gmask
		| (b << window->format->Bshift) & window->format->Bmask;
}

float xToScr(float x) {
	return (x + 1) / 2 * WIDTH;
}

float yToScr(float y) {
	return (1 - (y + 1) / 2) * HEIGHT;
}

void V_Quit() {
}

