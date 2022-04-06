#ifndef DEFINES_H
#define DEFINES_H

#include <SDL.h>

//#define DEBUG_OUTPUT

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#ifdef DEBUG_OUTPUT
#define DBG_MSG(_fmt) fprintf(stderr, "[%s:%d]: " _fmt, __FILE__, __LINE__)
#define DBG_MSG_ARGS(_fmt, ...) fprintf(stderr, "[%s:%d]: " _fmt, __FILE__, __LINE__, __VA_ARGS__)
#else
#define DBG_MSG(_fmt) ;
#define DBG_MSG_ARGS(_fmt, ...) ;
#endif
#ifndef VME_VERSION
#define VME_VERSION "unknown_version"
#endif

#define VME_PI 3.1415927f
#define PLAYER_HEIGHT 10
#define VME_LEFT	0x1
#define VME_RIGHT	0x2
#define PLAYER_MAXDIFF 0.95f


typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
} App;

struct Entity {
	double x, y;
	SDL_Texture* texture;
	void(*data);
};

enum LEVEL {
	MENU,
	GAME,
	GAME_TXT,
	FAILED
};

#endif // !DEFINES_H
