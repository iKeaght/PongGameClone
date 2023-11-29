#pragma once
#include "Vector2.h"
#include <SDL.h>
#include "Utils.h"


class Ball {
public:
	Vector2 position;
	SDL_Rect rect{ };

	Ball(Vector2 position);
	void DrawBall(SDL_Renderer* renderer);
};