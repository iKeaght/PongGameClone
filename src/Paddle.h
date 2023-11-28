#pragma once
#include "Vector2.h"
#include "SDL.h"

const int PADDLE_WIDTH = 12;
const int PADDLE_HEIGHT = 100;
class Paddle {
public: 
	Vector2 position;
	SDL_Rect rect{};
	Paddle(Vector2);
	void DrawPaddle(SDL_Renderer* renderer);
};