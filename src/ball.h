#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "player.h"

typedef struct {
	float
		size,
		speed, rotation,
		x, y,
		dx, dy;
	Player* player;
	uint8_t r, g, b;
} Ball;

void initBall(Ball* ball, Player* player_p);
void renderBall(Ball* ball, SDL_Renderer* renderer);
void updateBall(Ball* ball);
void ball_checkCollision(Ball* b);
void ball_moveVectorNormalise(float* x, float* y);

#endif // !BALL_H
