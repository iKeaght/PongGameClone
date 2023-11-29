#include "Ball.h"
#include "Utils.h"


Ball::Ball(Vector2 position, Vector2 velocity) : position(position), velocity(velocity) {
	rect.x = static_cast<int> (position.x);
	rect.y = static_cast<int> (position.y);
	rect.w = Utils::BALL_WIDTH;
	rect.h = Utils::BALL_HEIGHT;
}

void Ball::Update(float deltaTime)
{
	position += velocity * deltaTime;
}

void Ball::CollideWithPaddle(Utils::Contact const& contact)
{
	position.x += contact.penetration;
	velocity.x = -velocity.x;

	if (contact.type == Utils::CollisionType::Top) {
		velocity.y = -0.75f * Utils::BALL_SPEED;
	} 
	else if (contact.type == Utils::CollisionType::Bottom) {

		velocity.y = 0.75f * Utils::BALL_SPEED;
	}
}

void Ball::DrawBall(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}