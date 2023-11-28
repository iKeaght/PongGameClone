#include <iostream>
#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
bool running = true;

int main(int argc, char* args[]) {
	
	//Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Error with SDL_Init : " << SDL_GetError() << std::endl;
		return -1;
	};
	SDL_Window* gameWindow = SDL_CreateWindow("Pong", 300, 150, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer  = SDL_CreateRenderer(gameWindow, -1, 0);
	SDL_Event event;

	//Create ball
	Ball ball(Vector2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH/2.0f)));


	//CreatePaddle
	Paddle paddle1(Vector2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));
	Paddle paddle2(Vector2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - PADDLE_HEIGHT / 2.0f));


	//Game loop
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if(event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		//Draw middle bar
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			if (y % 5) {
				SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
			}
		}

		ball.DrawBall(renderer);
		paddle1.DrawPaddle(renderer);
		paddle2.DrawPaddle(renderer);
		SDL_RenderPresent(renderer);
	}

	//Clean up
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}