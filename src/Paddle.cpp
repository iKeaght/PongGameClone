#include "Paddle.h"
#include "Utils.h"

Paddle::Paddle(Vector2 position, Vector2 velocity) : position(position), velocity(velocity) {
	rect.x = static_cast<int> (position.x);
	rect.y = static_cast<int> (position.y);
	rect.w = Utils::PADDLE_WIDTH;
	rect.h = Utils::PADDLE_HEIGHT;
}

void Paddle::Update(float deltaTime)
{
	position += velocity * deltaTime;

	if (position.y < 0) {

		//prevent paddle from leaving the screen
		position.y = 0;
	}
	else if (position.y > (Utils::WINDOW_HEIGHT - Utils::PADDLE_HEIGHT)) {
		position.y = Utils::WINDOW_HEIGHT - Utils::PADDLE_HEIGHT;
	}
}

void Paddle::DrawPaddle(SDL_Renderer* renderer)
{
	rect.y = static_cast<int>(position.y);
	SDL_RenderFillRect(renderer, &rect);
}


