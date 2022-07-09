#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "v_main.h"

int main() {
	V_Init();

	bool running = true;
	SDL_Event event;
	while (running) {
		SDL_WaitEvent(&event);

		V_Tick();

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

