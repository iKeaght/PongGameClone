#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2.h"
class PlayerScore
{
public:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface{};
	SDL_Texture* texture{};
	SDL_Rect rect{};

	PlayerScore(Vector2 position, SDL_Renderer* renderer, TTF_Font* font);
	~PlayerScore();
	void Draw();
};

