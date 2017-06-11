/*
 * level.cpp
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#include "level.h"
#include "graphics.h"
#include <SDL2/SDL.h>

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
		mapName_(mapName),
		spawnPoint_(spawnPoint),
		size_(Vector2(0,0))
{
	this->loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//TEMPORARY CODE TO LOAD THE BACKGROUND
	this->backgroundTexture_ = SDL_CreateTextureFromSurface(graphics.getRenderer(),
			graphics.loadImage(globals::CONTENT_BACKGROUNDS_BKBLUE));

	this->size_ = Vector2(1280, 960);
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	//Draw the background

	SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect;

	for (int x = 0; x < this->size_.x / 64; x++) {
		for (int y = 0; y < this->size_.y / 64; y++) {
			destRect.x = x * 64 * globals::SPRITE_SCALE;
			destRect.y = y * 64 * globals::SPRITE_SCALE;
			destRect.w = 64 * globals::SPRITE_SCALE;
			destRect.h = 64 * globals::SPRITE_SCALE;
			graphics.blitSurface(this->backgroundTexture_, &sourceRect, &destRect);
		}
	}
}



