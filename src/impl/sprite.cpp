/*
 * sprite.cpp
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#include <stdio.h>
#include <cmath>

#include "sprite.h"
#include "graphics.h"
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

	//Initializes the bounding box around the sprite that will be used for
	//collision detection
	this->boundingBox_ = Rectangle(this->x_, this->y_, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);

}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
	//By multiplying by globals::SPRITE_SCALE, I'm telling to double the pixels (twice the size, double scale)
	//static_cast<int> to avoid narrowing
	SDL_Rect destinationRectangle = {x, y, static_cast<int>(this->sourceRectangle_.w * globals::SPRITE_SCALE),
			static_cast<int>(this->sourceRectangle_.h * globals::SPRITE_SCALE)};
	graphics.blitSurface(this->spriteSheet_, &this->sourceRectangle_, &destinationRectangle);
}

void Sprite::update() {
	this->boundingBox_ = Rectangle(this->x_, this->y_,
			this->sourceRectangle_.w * globals::SPRITE_SCALE,
			this->sourceRectangle_.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const {
	return this->boundingBox_;
}

//Determine which side the collision happened on
const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
	//How much the sprite rectangle is inside the other rectangle side
	int amountRight, amountLeft, amountTop, amountBottom;
	amountRight = this->boundingBox_.getRight() - other.getLeft();
	amountLeft = this->boundingBox_.getLeft() - other.getRight();
	amountTop = this->boundingBox_.getTop() - other.getBottom();
	amountBottom = this->boundingBox_.getBottom() - other.getTop();

	int vals[4] = { abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
		lowest == abs(amountRight) ? sides::RIGHT :
		lowest == abs(amountLeft) ? sides::LEFT :
		lowest == abs(amountTop) ? sides::TOP :
		lowest == abs(amountBottom) ? sides::BOTTOM :
		sides::NONE;
}
