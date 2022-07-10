#include "v_main.h"


SDL_Surface* window;

float V_viewOffs[2];
float V_viewScale[2];


void V_Init() {
	SDL_WM_SetCaption("SDL1.2 Software Rasterizer 今回は行ける気がする！", NULL);
	window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

	V_viewOffs[0] = 0;
	V_viewOffs[1] = 0;
	V_viewScale[0] = 10;
	V_viewScale[1] = 10;
}

void V_Tick() {
	V_ClearScreen(0, 0, 0);

	float gray[][2] = {
		{-0.5, 0}, {0.5, 0}, {0, 1.5},
	};
	float blue[][2] = {
		{-0.25, 0.35}, {0.25, 0.35}, {0, 1.5},
	};
	float black[][2] = {
		{-0.1, 1}, {0.1, 1}, {0, 1.5},
	};

	V_RasterizeTriangle(gray, 0x33, 0x33, 0x33);
	V_RasterizeTriangle(blue, 0, 0, 0xAA);
	V_RasterizeTriangle(black, 0x11, 0x11, 0x11);
}

void V_SetPixel(int x, int y, int r, int g, int b) {
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) return;

	((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
		(r << window->format->Rshift) & window->format->Rmask
		| (g << window->format->Gshift) & window->format->Gmask
		| (b << window->format->Bshift) & window->format->Bmask;
}

void V_SetRow(int y, int r, int g, int b) {
	for (int x = 0; x < WIDTH; x++)
		((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
			(r << window->format->Rshift) & window->format->Rmask
			| (g << window->format->Gshift) & window->format->Gmask
			| (b << window->format->Bshift) & window->format->Bmask;
}

void V_ClearScreen(int r, int g, int b) {
	for (int y = 0; y < HEIGHT; y++) {
		V_SetRow(y, r, g, b);
		V_SetPixel(0, y, 0xFF, 0, 0);
	}
}

float xToScr(float x) {
	return ((x - V_viewOffs[0]) / V_viewScale[0] * HEIGHT / WIDTH + 1) / 2 * WIDTH;
}

float yToScr(float y) {
	return (1 - ((y - V_viewOffs[1]) / V_viewScale[1] + 1) / 2) * HEIGHT;
}

void V_Quit() {
	SDL_FreeSurface(window);
}

