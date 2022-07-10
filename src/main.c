#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "v_main.h"
#include "g_main.h"


#define FRAMERATE 60

int pressedButtons = 0;

float gameDelta = 0;

SDL_Joystick* joystick;

int main() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	V_Init();
	G_Init();

	joystick = SDL_JoystickOpen(0);

	int frames = 0;
	int lastSecond = SDL_GetTicks();
	int startOfFrame;

	bool running = true;
	SDL_Event event;
	while (running) {
		startOfFrame = SDL_GetTicks();

		G_Tick();

		V_Tick();

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 0) pressedButtons |= IN_B;
				if (event.jbutton.button == 1) pressedButtons |= IN_A;
				
				break;
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button == 0) pressedButtons &= ~IN_B;
				if (event.jbutton.button == 1) pressedButtons &= ~IN_A;
				
				break;
			case SDL_JOYHATMOTION:
				pressedButtons &= ~(IN_UP | IN_DOWN | IN_LEFT | IN_RIGHT);
				if (event.jhat.value & SDL_HAT_UP) pressedButtons |= IN_UP;
				if (event.jhat.value & SDL_HAT_DOWN) pressedButtons |= IN_DOWN;
				if (event.jhat.value & SDL_HAT_LEFT) pressedButtons |= IN_LEFT;
				if (event.jhat.value & SDL_HAT_RIGHT) pressedButtons |= IN_RIGHT;
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		SDL_Flip(window);

		int delta = SDL_GetTicks() - startOfFrame;
		if (1000 / FRAMERATE > delta) SDL_Delay(1000 / FRAMERATE - delta);

		int now = SDL_GetTicks();
		frames++;
		if (now - lastSecond > 1000) {
			lastSecond = now;
			printf("Frames per second: %d\n", frames);
			frames = 0;
		}

		gameDelta = (SDL_GetTicks() - startOfFrame) / 1000.0;
	}

	G_Quit();
	V_Quit();
	SDL_Quit();
	return 0;
}

