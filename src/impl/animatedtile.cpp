/*
 * animatedtile.cpp
 *
 *  Created on: 20 de jun de 2017
 *      Author: jcfausto
 */

#include <vector>
#include "animatedtile.h"
#include "graphics.h"
#include "tile.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tilePositions, int duration,
		SDL_Texture* tileset, Vector2 size, Vector2 position) :
			Tile(tileset, size, tilePositions.at(0), position),
			tilesetPositions_(tilePositions),
			duration_(duration),
			tileToDraw_(0)
{}

void AnimatedTile::update(int elapsedTime) {
	//Timer code
	if (this->amountOfTime <= 0) {
		if (this->tileToDraw_ == this->tilesetPositions_.size() -1) {
			this->tileToDraw_ = 0;
		} else {
			this->tileToDraw_++;
		}
		this->amountOfTime = this->duration_;
	} else {
		this->amountOfTime -= elapsedTime;
	}

	Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics &graphics) {
	SDL_Rect destRect = { this->position_.x, this->position_.y,
		this->size_.x * globals::SPRITE_SCALE, this->size_.y * globals::SPRITE_SCALE };

	SDL_Rect srcRect = { this->tilesetPositions_.at(this->tileToDraw_).x,
			this->tilesetPositions_.at(this->tileToDraw_).y,
			this->size_.x, this->size_.y };

	graphics.blitSurface(this->tileset_, &srcRect, &destRect);
}




