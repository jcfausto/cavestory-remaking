/*
 * graphics.cpp
 *
 *  Created on: 7 de jun de 2017
 *      Author: jcfausto
 *
 *  Holds all information dealing with graphics for the game
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "graphics.h"
#include "globals.h"

//Constructor
Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->window_, &this->renderer_);
	SDL_SetWindowTitle(this->window_, "Cavestory Remake C++");
}

//Desctructor
Graphics::~Graphics() {
	SDL_DestroyWindow(this->window_);
	SDL_DestroyRenderer(this->renderer_);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (this->spriteSheets_.count(filePath) == 0) {
		this->spriteSheets_[filePath] = IMG_Load(filePath.c_str());
	}
	return this->spriteSheets_[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(this->renderer_, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
	SDL_RenderPresent(this->renderer_);
}

void Graphics::clear() {
	SDL_RenderClear(this->renderer_);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->renderer_;
}
