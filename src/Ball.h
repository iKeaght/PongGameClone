#pragma once
#include "Vector2.h"
#include <SDL.h>

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

class Ball {
public:
	Vector2 position;
	SDL_Rect rect{ };

	Ball(Vector2 position);
	void DrawBall(SDL_Renderer* renderer);
};