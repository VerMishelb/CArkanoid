#include "game.h"

#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "ball.h"

App app;
char VMEstop = 0;
Player player;
Ball ball;

int VMEinit(const char* w_name) {
	srand(time(NULL));
	DBG_MSG_ARGS("Starting VME %s", VME_VERSION);

	app.renderer = NULL;
	app.window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		DBG_MSG("Could not initialise SDL\n");
		return -1;
	}
	app.window = SDL_CreateWindow(w_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!app.window) {
		DBG_MSG("Could not initialise the window\n");
		return -1;
	}
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!app.renderer) {
		DBG_MSG("Could not initialise the renderer\n");
		return -1;
	}
	
	initPlayer(&player);
	initBall(&ball, &player);

	return 0;
}

int VMEstart(void) {
	if (VMEinit("Arcanoid [КВБО-03-21 Беликов Михаил] " __DATE__)) {
		return -1;
	}

	while (!VMEstop) {
		VMEinput();
		VMEupdate();
		VMErender();
	}

	VMEcleanup();

	return 0;
}

void VMEinput() {
	SDL_Event _event;
	while (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_QUIT || (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_ESCAPE)) {
			VMEstop = 1;
		}
		inputPlayer(&player, &_event);
	}
}

void VMEupdate(void) {
	updatePlayer(&player);
	updateBall(&ball);
}

void VMErender() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);

	renderPlayer(&player, app.renderer);
	renderBall(&ball, app.renderer);

	SDL_RenderPresent(app.renderer);
}

void VMEcleanup() {
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}