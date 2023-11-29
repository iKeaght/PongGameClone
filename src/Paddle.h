#pragma once
#include "Vector2.h"
#include "SDL.h"
#include "Utils.h"


class Paddle {
public: 
	Vector2 position;
	Vector2 velocity;
	SDL_Rect rect{};


	Paddle(Vector2 position, Vector2 velocity);
	void Update(float deltaTime);
	void DrawPaddle(SDL_Renderer* renderer);
};