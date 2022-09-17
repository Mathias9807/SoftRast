#include "v_main.h"
#include "g_main.h"


SDL_Surface* window;

float V_viewOffs[2];
float V_viewScale[2];

#define N_STARS 16
float starXPos[N_STARS];
float starYOffs = -10;


void V_Init() {
	SDL_WM_SetCaption("SDL1.2 Software Rasterizer 今回は行ける気がする！", NULL);
	window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

	V_viewOffs[0] = 0;
	V_viewOffs[1] = 0;
	V_viewScale[0] = 8;
	V_viewScale[1] = 8;

	for (int i = 0; i < N_STARS; i++)
		starXPos[i] = ((float) rand() / RAND_MAX) * 2 - 1;
}

void V_Tick() {
	V_ClearScreen(0, 0, 0);

	// Draw stars as background
	float minor = 0.06, major = 0.15;
	float star[] = {
		major, -0.10, 0, 0.18, -major, -0.10,
		major, 0.10, 0, -0.18, -major, 0.10,
	};

	starYOffs -= gameDelta * 5;
	for (int i = 0; i < N_STARS; i++) {
		float y = starYOffs + (float) i / N_STARS * V_viewScale[1];
		V_DrawTriangles(star, 2,
			starXPos[i] * V_viewScale[0] * WIDTH/HEIGHT * 0.5,
			fmod(y, V_viewScale[1]) * 2 + V_viewScale[1],
			0x22, 0x22, 0x22);
		V_DrawTriangles(star, 2,
			-starXPos[i] * V_viewScale[0] * WIDTH/HEIGHT,
			(fmod(y, V_viewScale[1]) + V_viewScale[1] / 2) * 3,
			0x22, 0x22, 0x22);
	}

	for (ListEntry* e = g_entities.first; e; e = e->next)
		G_EntityRender((Entity*) e->value);
}

void V_SetPixel(int x, int y, int r, int g, int b) {
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) return;

	((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
		(r << window->format->Rshift & window->format->Rmask)
		| (g << window->format->Gshift & window->format->Gmask)
		| (b << window->format->Bshift & window->format->Bmask);
}

void V_SetRow(int y, int r, int g, int b) {
	for (int x = 0; x < WIDTH; x++)
		((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
			(r << window->format->Rshift & window->format->Rmask)
			| (g << window->format->Gshift & window->format->Gmask)
			| (b << window->format->Bshift & window->format->Bmask);
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

