#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <SDL/SDL.h>

#define WIDTH 640
#define HEIGHT 480

SDL_Surface* window;

void setPixel(int x, int y, int r, int g, int b) {
	((int*)window->pixels)[window->pitch / sizeof(int) * y + x] =
		(r << window->format->Rshift) & window->format->Rmask
		| (g << window->format->Gshift) & window->format->Gmask
		| (b << window->format->Bshift) & window->format->Bmask;
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

float lerp(float a, float b, float p) {
	return a * (1 - p) + b * p;
}

void lerp2(float *a, float *b, float *r, float p) {
	r[0] = a[0] * (1 - p) + b[0] * p;
	r[1] = a[1] * (1 - p) + b[1] * p;
}

float xToScr(float x) {
	return (x + 1) / 2 * WIDTH;
}

float yToScr(float y) {
	return (1 - (y + 1) / 2) * HEIGHT;
}

void rasterizeTriangle(float v[3][2], char r, char g, char b) {
	// Split the triangle in half by its middle point, then render each half individually
	// Find the vertical point order
	int yMax = 0, yMid = 1, yMin = 2;
	if (v[yMin][1] > v[yMid][1]) swap(&yMin, &yMid);
	if (v[yMid][1] > v[yMax][1]) swap(&yMax, &yMid);
	if (v[yMin][1] > v[yMid][1]) swap(&yMin, &yMid);

	int xMax = 0, xMid = 1, xMin = 2;
	if (v[xMin][0] > v[xMid][0]) swap(&xMin, &xMid);
	if (v[xMid][0] > v[xMax][0]) swap(&xMax, &xMid);
	if (v[xMin][0] > v[xMid][0]) swap(&xMin, &xMid);

	// // As a test, fill in a bounding square around the triangle
	// for (int x = xToScr(v[xMin][0]); x < xToScr(v[xMax][0]); x++) {
	// 	for (int y = yToScr(v[yMax][1]); y < yToScr(v[yMin][1]); y++) {
	// 		setPixel(x, y, 0xAA, 0xBB, 0xCC);
	// 	}
	// } // WORKS!

	// Draw top half of triangle
	// Triangle draw algorithm takes the two vertical lines of the triangle and fills in whole lines from top to bottom

	// Take the virtual point horizontally opposite to the vertical midpoint
	float p = (v[yMax][1] - v[yMid][1]) / (v[yMax][1] - v[yMin][1]);
	float vMid[2] = {lerp(v[yMax][0], v[yMin][0], p), v[yMid][1]};
	printf("vMid = [%f, %f]\n", vMid[0], vMid[1]);

	float *midLeft, *midRight;
	if (v[yMid][0] < vMid[0]) {
		midLeft = v[yMid];
		midRight = vMid;
	}else {
		midRight = v[yMid];
		midLeft = vMid;
	}

	// Each pixel that has its top left corner inside the triangle should be filled
	// Loop through the vertical span of pixels the triangle covers
	for (int y = ceil(yToScr(v[yMax][1])); y < yToScr(v[yMid][1]); y++) {
		
		// Inter left and right lines
		float p = (yToScr(v[yMax][1]) - y) / (yToScr(v[yMax][1]) - yToScr(v[yMid][1]));
		float leftPoint[2], rightPoint[2];
		lerp2(v[yMax], midLeft, leftPoint, p);
		lerp2(v[yMax], midRight, rightPoint, p);

		// Fill this whole line
		for (int x = ceil(xToScr(leftPoint[0])); x < xToScr(rightPoint[0]); x++) {
			setPixel(x, y, r, b, g);
		}
	}

	// Draw the lower triangle half
	for (int y = ceil(yToScr(v[yMid][1])); y < yToScr(v[yMin][1]); y++) {
		
		// Inter left and right lines
		float p = (y - yToScr(v[yMid][1])) / (yToScr(v[yMin][1]) - yToScr(v[yMid][1]));
		float leftPoint[2], rightPoint[2];
		lerp2(midLeft,  v[yMin], leftPoint, p);
		lerp2(midRight, v[yMin], rightPoint, p);

		// Fill this whole line
		for (int x = ceil(xToScr(leftPoint[0])); x < xToScr(rightPoint[0]); x++) {
			setPixel(x, y, r, b, g);
		}
	}
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("SDL1.2 Software Rasterizer 今回は行ける気がする！", NULL);
	window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

	float v[][2] = {
		{-0.5, 0}, {0.5, -0.5}, {0, 0.5},

		{-0.5, 0}, {-0.5, 0.5}, {0, 0.5},
		{-0.5, 0}, {0.5, -0.5}, {-0.5, -0.5},
		{0.5, 0.5}, {0.5, -0.5}, {0, 0.5},
	};

	bool running = true;
	SDL_Event event;
	while (running) {
		SDL_WaitEvent(&event);

		for (int i = 0; i < sizeof(v) / sizeof(float[3][2]); i++)
			rasterizeTriangle(v + 3 * i, 0xAA, 0x44 + 0x20*i, 0x88 + 0x10*i);

		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		}

		SDL_Flip(window);
	}

	SDL_FreeSurface(window);
	SDL_Quit();
	return 0;
}

