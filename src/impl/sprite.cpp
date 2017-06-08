/*
 * sprite.cpp
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#include "sprite.h"
#include "graphics.h"
#include <stdio.h>
#include "globals.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY):
				x_(posX),
				y_(posY)
{
	this->sourceRectangle_.x = sourceX;
	this->sourceRectangle_.y = sourceY;
	this->sourceRectangle_.w = width;
	this->sourceRectangle_.h = height;

	this->spriteSheet_ = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	if (this->spriteSheet_ == NULL) {
		printf("\nError: Unable to load image\n");
	}

}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
	//By multiplying by globals::SPRITE_SCALE, I'm telling to double the pixels (twice the size, double scale)
	//static_cast<int> to avoid narrowing
	SDL_Rect destinationRectangle = {x, y, static_cast<int>(this->sourceRectangle_.w * globals::SPRITE_SCALE),
			static_cast<int>(this->sourceRectangle_.h * globals::SPRITE_SCALE)};
	graphics.blitSurface(this->spriteSheet_, &this->sourceRectangle_, &destinationRectangle);
}

void Sprite::update() {}
