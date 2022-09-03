#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "logger.h"
#include "v_main.h"
#include "g_main.h"


#define FRAMERATE 60

int heldButtons = 0;
int pressedButtons = 0;

float gameDelta = 0;
float gameClock = 0;

SDL_Joystick* joystick;

int main() {
	srand(time(NULL));
	L_InitLogger(0);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	V_Init();
	G_Init();

	joystick = SDL_JoystickOpen(0);

	int frames = 0;
	int lastSecond = SDL_GetTicks();
	int startOfFrame;

	bool running = true;
	SDL_Event event;
	int prevHeldButtons;
	while (running) {
		startOfFrame = SDL_GetTicks();
		gameClock = startOfFrame / 1000.0;

		G_Tick();

		V_Tick();

		prevHeldButtons = heldButtons;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 0) heldButtons |= IN_B;
				if (event.jbutton.button == 1) heldButtons |= IN_A;
				
				break;
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button == 0) heldButtons &= ~IN_B;
				if (event.jbutton.button == 1) heldButtons &= ~IN_A;
				
				break;
			case SDL_JOYHATMOTION:
				heldButtons &= ~(IN_UP | IN_DOWN | IN_LEFT | IN_RIGHT);
				if (event.jhat.value & SDL_HAT_UP) heldButtons |= IN_UP;
				if (event.jhat.value & SDL_HAT_DOWN) heldButtons |= IN_DOWN;
				if (event.jhat.value & SDL_HAT_LEFT) heldButtons |= IN_LEFT;
				if (event.jhat.value & SDL_HAT_RIGHT) heldButtons |= IN_RIGHT;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_u) heldButtons |= IN_A;
				if (event.key.keysym.sym == SDLK_o) heldButtons |= IN_B;

				if (event.key.keysym.sym == SDLK_w) heldButtons |= IN_UP;
				if (event.key.keysym.sym == SDLK_s) heldButtons |= IN_DOWN;
				if (event.key.keysym.sym == SDLK_a) heldButtons |= IN_LEFT;
				if (event.key.keysym.sym == SDLK_d) heldButtons |= IN_RIGHT;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_u) heldButtons &= ~IN_A;
				if (event.key.keysym.sym == SDLK_o) heldButtons &= ~IN_B;

				if (event.key.keysym.sym == SDLK_w) heldButtons &= ~IN_UP;
				if (event.key.keysym.sym == SDLK_s) heldButtons &= ~IN_DOWN;
				if (event.key.keysym.sym == SDLK_a) heldButtons &= ~IN_LEFT;
				if (event.key.keysym.sym == SDLK_d) heldButtons &= ~IN_RIGHT;
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		pressedButtons = heldButtons & ~prevHeldButtons;

		SDL_Flip(window);

		int delta = SDL_GetTicks() - startOfFrame;
		if (1000 / FRAMERATE > delta) SDL_Delay(1000 / FRAMERATE - delta);

		int now = SDL_GetTicks();
		frames++;
		if (now - lastSecond > 1000) {
			lastSecond = now;
			L_Log("Frames per second: %d\n", frames);
			frames = 0;
		}

		gameDelta = (SDL_GetTicks() - startOfFrame) / 1000.0;
	}

	G_Quit();
	V_Quit();
	SDL_Quit();
	return 0;
}

