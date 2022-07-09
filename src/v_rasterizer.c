#include "v_main.h"


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

void V_RasterizeTriangle(float v[3][2], char r, char g, char b) {
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

	// Draw top half of triangle
	// Triangle draw algorithm takes the two vertical lines of the triangle and fills in whole lines from top to bottom

	// Take the virtual point horizontally opposite to the vertical midpoint
	float p = (v[yMax][1] - v[yMid][1]) / (v[yMax][1] - v[yMin][1]);
	float vMid[2] = {lerp(v[yMax][0], v[yMin][0], p), v[yMid][1]};

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
			V_SetPixel(x, y, r, b, g);
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
			V_SetPixel(x, y, r, b, g);
		}
	}
}

