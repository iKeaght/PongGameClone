#pragma once
#include "Vector2.h"
#include <SDL.h>
#include "Utils.h"


class Ball {
public:
	Vector2 position;
	Vector2 velocity;
	SDL_Rect rect{ };

	Ball(Vector2 position, Vector2 velocity);
	void Update(float deltaTime);
	void CollideWithPaddle(Utils::Contact const& contact);
	void CollideWithWalls(Utils::Contact const& contact);
	void DrawBall(SDL_Renderer* renderer);
};