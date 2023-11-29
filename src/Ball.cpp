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
	position.x += contact.penetrationAmount;
	velocity.x = -velocity.x;

	if (contact.type == Utils::CollisionType::Top) {
		velocity.y = -0.75f * Utils::BALL_SPEED;
	} 
	else if (contact.type == Utils::CollisionType::Bottom) {

		velocity.y = 0.75f * Utils::BALL_SPEED;
	}
}

void Ball::CollideWithWalls(Utils::Contact const& contact)
{
	if (contact.type == Utils::CollisionType::Top || contact.type == Utils::CollisionType::Bottom) {
		position.y += contact.penetrationAmount;
		velocity.y = -velocity.y;
	}
	else if (contact.type == Utils::CollisionType::Left) {
		position.x = Utils::WINDOW_WIDTH / 2.0f;
		position.y = Utils::WINDOW_HEIGHT / 2.0f;
		velocity.x = Utils::BALL_SPEED;
		velocity.y = 0.75f * Utils::BALL_SPEED;
	}
	else if (contact.type == Utils::CollisionType::Right) {
		position.x = Utils::WINDOW_WIDTH / 2.0f;
		position.y = Utils::WINDOW_HEIGHT / 2.0f;
		velocity.x = -Utils::BALL_SPEED;
		velocity.y = 0.75f * Utils::BALL_SPEED;
	}
}

void Ball::DrawBall(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}