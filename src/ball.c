#include <math.h>
#include <stdlib.h>
#include "defines.h"
#include "ball.h"

#ifdef DEBUG_OUTPUT
#include <stdio.h>
#endif

void ball_moveVectorNormalise(float* x, float* y) {
	float vec_length = sqrt(*x * *x + *y * *y);
	*x /= vec_length;
	*y /= vec_length;
}

void initBall(Ball* ball, Player* player_p) {
	ball->r = rand() % 245 + 10;
	ball->g = rand() % 245 + 10;
	ball->b = rand() % 245 + 10;

	ball->speed = 5.0f;
	ball->size = 10;
	ball->x = WINDOW_WIDTH / 2.0;
	ball->y = WINDOW_HEIGHT / 2.0;
	ball->rotation = VME_PI / 3.f;
	//ball->rotation = VME_PI * (rand() % extra_balls_amnt / (float)extra_balls_amnt);
	ball->dx = cosf(ball->rotation);
	ball->dy = sinf(ball->rotation);
	ball_moveVectorNormalise(&ball->dx, &ball->dy);
	ball->dx *= ball->speed;
	ball->dy *= ball->speed;
	ball->player = player_p;
}

void updateBall(Ball* ball) {
	ball_checkCollision(ball);
	ball->x += ball->dx;
	ball->y += ball->dy;
}

void renderBall(Ball* ball, SDL_Renderer* renderer) {
	float b_sized2 = ball->size / 2.f;
	SDL_FRect p_rect = {
		(ball->x) - b_sized2, (ball->y) - b_sized2,
		(ball->size), (ball->size) };
	DBG_MSG_ARGS(__FUNCTION__" {%f %f %f %f}\n", p_rect.x, p_rect.y, p_rect.w, p_rect.h);
	SDL_SetRenderDrawColor(renderer, ball->r, ball->g, ball->b, 255);
	SDL_RenderFillRectF(renderer, &p_rect.x);
}

void ball_checkCollision(Ball* b) {
	float b_sized2 = b->size / 2.f;
	if (b->x - b_sized2 < 0 || b->x + b_sized2 > WINDOW_WIDTH) {
		//DBG_MSG("hit x\n");
		b->dx = -b->dx;
	}
	if (b->y - b_sized2 < 0 || b->y + b_sized2 > WINDOW_HEIGHT) {
		//DBG_MSG("hit y\n");
		b->dy = -b->dy;
	}

	if (
		(b->y + b_sized2) > (b->player->y - PLAYER_HEIGHT / 2.0) &&
		(b->y - b_sized2) < (b->player->y + PLAYER_HEIGHT / 2.0) &&
		(b->x + b_sized2) > (b->player->x - b->player->width / 2.0) &&
		(b->x - b_sized2) < (b->player->x + b->player->width / 2.0)
		)
	{
		//DBG_MSG("COLLISION!\n");
		float difference = ((b->x) - (b->player->x)) * 2 / b->player->width;
		//float something_random = VME_PI / 180.f * ((rand() % (extra_balls_amnt * 2) - extra_balls_amnt + 1) / (float)extra_balls_amnt);
		if (difference > PLAYER_MAXDIFF) {
			difference = PLAYER_MAXDIFF;
		}
		if (difference < -PLAYER_MAXDIFF) {
			difference = -PLAYER_MAXDIFF;
		}
		b->rotation = acosf(difference);// +something_random - (something_random / 2.f);
		b->dx = cosf(b->rotation);
		b->dy = -sinf(b->rotation);
		ball_moveVectorNormalise(&b->dx, &b->dy);
		b->speed += 0.1f;
		b->dx *= b->speed;
		b->dy *= b->speed;
	}
}