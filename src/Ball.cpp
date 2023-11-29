#include "Ball.h"


Ball::Ball(Vector2 position) : position(position) {
	rect.x = static_cast<int> (position.x);
	rect.y = static_cast<int> (position.y);
	rect.w = Utils::BALL_WIDTH;
	rect.h = Utils::BALL_HEIGHT;
}

void Ball::DrawBall(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}