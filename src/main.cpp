#include <iostream>
#include <SDL.h>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
bool running = true;

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* gameWindow = SDL_CreateWindow("Pong", 300, 300, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer  = SDL_CreateRenderer(gameWindow, -1, 0);
	SDL_Event event;
	//SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &gameWindow, &renderer);
	while (running) {
		SDL_PollEvent(&event);
		
	}

	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}