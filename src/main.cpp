#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Ball.h"
#include "Paddle.h"
#include "PlayerScore.h"
#include "Utils.h"
#include <chrono>
bool running = true;
float deltaTime = 0.0f;
enum Buttons {
	Paddle1Up,
	Paddle1Down,
	Paddle2Up,
	Paddle2Down,
};
bool buttons[4] = {};

//Using Separating Axis Theorem (SAT) for checks
Utils::Contact CheckPaddleCollisions(Ball const& ball, Paddle const& paddle) {
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + Utils::BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + Utils::BALL_HEIGHT;

	float paddleLeft = paddle.position.x;
	float paddleRight = paddle.position.x + Utils::PADDLE_WIDTH;
	float paddleTop = paddle.position.y;
	float paddleBottom = paddle.position.y + Utils::PADDLE_HEIGHT;

	Utils::Contact contact{};
	if (ballLeft >= paddleRight)
	{
		return contact;
	}

	if (ballRight <= paddleLeft)
	{
		return contact;
	}

	if (ballTop >= paddleBottom)
	{
		return contact;
	}

	if (ballBottom <= paddleTop)
	{
		return contact;
	}
	float paddleRangeUpper = paddleBottom - (2.0f * Utils::PADDLE_HEIGHT / 3.0f);
	float paddleRangeMiddle = paddleBottom - (Utils::PADDLE_HEIGHT / 3.0f);

	//left side
	if (ball.velocity.x < 0) {
		contact.penetrationAmount = paddleRight - ballLeft;
	}
	//right side of the screen
	else if (ball.velocity.x > 0) {
		contact.penetrationAmount = paddleLeft - ballRight;
	}

	if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper)) {
		contact.type = Utils::CollisionType::Top;
	}
	else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle)) {
		contact.type = Utils::CollisionType::Middle;
	}
	else {
		contact.type = Utils::CollisionType::Bottom;
	}


	return contact;
}
//Using Separating Axis Theorem (SAT) for checks
Utils::Contact CheckWallCollision(Ball const& ball) {
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + Utils::BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + Utils::BALL_HEIGHT;

	Utils::Contact contact{};
	if (ballLeft < 0.0f) {
		contact.type = Utils::CollisionType::Left;
	}
	else if (ballRight > Utils::WINDOW_WIDTH) {
		contact.type = Utils::CollisionType::Right;
	}
	else if (ballTop < 0.0f) {
		contact.type = Utils::CollisionType::Top;
		contact.penetrationAmount = -ballTop;
	}
	else if (ballBottom > Utils::WINDOW_HEIGHT) {
		contact.type = Utils::CollisionType::Bottom;
		contact.penetrationAmount = Utils::WINDOW_HEIGHT - ballBottom;
	}
	return contact;
}
int main(int argc, char* args[]) {

	//Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Error with SDL_Init : " << SDL_GetError() << std::endl;
		return -1;
	};

	TTF_Init();
	SDL_Window* gameWindow = SDL_CreateWindow("Pong", 300, 150, Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(gameWindow, -1, 0);
	SDL_Event event;

	//Score
	TTF_Font* font = TTF_OpenFont("./Assets/font/Roboto-Black.ttf", 40);
	PlayerScore player1ScoreText(Vector2(Utils::WINDOW_WIDTH / 4, 20), renderer, font);
	PlayerScore player2ScoreText(Vector2(3 * Utils::WINDOW_WIDTH / 4, 20), renderer, font);

	//Create ball
	Ball ball(Vector2((Utils::WINDOW_WIDTH / 2.0f) - (Utils::BALL_WIDTH / 2.0f), (Utils::WINDOW_HEIGHT / 2.0f) - (Utils::BALL_WIDTH / 2.0f)), Vector2(Utils::BALL_SPEED, 0.0f));
	//CreatePaddle
	Paddle paddle1(Vector2(50.0f, (Utils::WINDOW_HEIGHT / 2.0f) - (Utils::PADDLE_HEIGHT / 2.0f)), Vector2(0.0f, 0.0f));
	Paddle paddle2(Vector2(Utils::WINDOW_WIDTH - 50.0f, (Utils::WINDOW_HEIGHT / 2.0f) - Utils::PADDLE_HEIGHT / 2.0f), Vector2(0.0f, 0.0f));


	//Game loop
	while (running) {


		auto startTime = std::chrono::high_resolution_clock::now();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				else if (event.key.keysym.sym == SDLK_z)
				{
					buttons[Buttons::Paddle1Up] = true;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					buttons[Buttons::Paddle1Down] = true;
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					buttons[Buttons::Paddle2Up] = true;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					buttons[Buttons::Paddle2Down] = true;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_z)
				{
					buttons[Buttons::Paddle1Up] = false;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					buttons[Buttons::Paddle1Down] = false;
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					buttons[Buttons::Paddle2Up] = false;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					buttons[Buttons::Paddle2Down] = false;
				}
			}
		}

		if (buttons[Buttons::Paddle1Up])
		{
			paddle1.velocity.y = -Utils::PADDLE_SPEED;
		}
		else if (buttons[Buttons::Paddle1Down])
		{
			paddle1.velocity.y = Utils::PADDLE_SPEED;
		}
		else
		{
			paddle1.velocity.y = 0.0f;
		}

		if (buttons[Buttons::Paddle2Up])
		{
			paddle2.velocity.y = -Utils::PADDLE_SPEED;
		}
		else if (buttons[Buttons::Paddle2Down])
		{
			paddle2.velocity.y = Utils::PADDLE_SPEED;
		}
		else
		{
			paddle2.velocity.y = 0.0f;
		}

		paddle1.Update(deltaTime);
		paddle2.Update(deltaTime);
		ball.Update(deltaTime);
		Utils::Contact contactPaddle1 = CheckPaddleCollisions(ball, paddle1);
		Utils::Contact contactPaddl2 = CheckPaddleCollisions(ball, paddle2);
		Utils::Contact contactWalls = CheckWallCollision(ball);
		if (contactPaddle1.type != Utils::CollisionType::None) {
			ball.CollideWithPaddle(contactPaddle1);
		}
		else if (contactPaddl2.type != Utils::CollisionType::None) {
			ball.CollideWithPaddle(contactPaddl2);
		}
		else if (contactWalls.type != Utils::CollisionType::None) {
			ball.CollideWithWalls(contactWalls);
		}

		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		//Draw middle bar
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		for (int y = 0; y < Utils::WINDOW_HEIGHT; y++) {
			if (y % 5) {
				SDL_RenderDrawPoint(renderer, Utils::WINDOW_WIDTH / 2, y);
			}
		}

		ball.DrawBall(renderer);
		paddle1.DrawPaddle(renderer);
		paddle2.DrawPaddle(renderer);

		player1ScoreText.Draw();
		player2ScoreText.Draw();
		SDL_RenderPresent(renderer);


		auto stopTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}

	//Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gameWindow);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}