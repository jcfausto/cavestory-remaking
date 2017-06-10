/*
 * animatedsprite.cpp
 *
 *  Created on: 9 de jun de 2017
 *      Author: jcfausto
 *
 *  Animates our sprites
 */

#include <string>
#include "graphics.h"
#include "sprite.h"
#include "animatedsprite.h"
#include <vector>

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY, float timeToUpdate) :
				Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
				timeToUpdate_(timeToUpdate),
			 	currentAnimationOnce_(false),
				currentAnimation_(""),
				frameIndex_(0),
				timeElapsed_(0),
				visible_(true)
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;

	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}

	this->animations_.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));

	this->offsets_.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
	this->animations_.clear();
	this->offsets_.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->currentAnimationOnce_ = once;

	if (this->currentAnimation_ != animation) {
		this->currentAnimation_ = animation;
		this->frameIndex_ = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) {
	this->visible_ = visible;
}

void AnimatedSprite::stopAnimation() {
	this->frameIndex_ = 0;
	this->animationDone(this->currentAnimation_);
}

void AnimatedSprite::update(int elapsedTime) {
	Sprite::update();

	this->timeElapsed_ += elapsedTime;

	if (this->timeElapsed_ > this->timeToUpdate_) { //Means that we need to change the frame
		this->timeElapsed_ -= timeToUpdate_;
		if (this->frameIndex_ < this->animations_[this->currentAnimation_].size() - 1) {
			this->frameIndex_++;
		} else {
			if (this->currentAnimationOnce_ == true) {
				this->setVisible(false);
			}
			this->frameIndex_ = 0;
			this->animationDone(this->currentAnimation_);
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
	if (this->visible_) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->offsets_[this->currentAnimation_].x;
		destinationRectangle.y = y + this->offsets_[this->currentAnimation_].y;
		destinationRectangle.w = this->sourceRectangle_.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->sourceRectangle_.h * globals::SPRITE_SCALE;

		//TODO: Refactor candiate.
		std::vector<SDL_Rect> currentAnimationFrames;
		currentAnimationFrames = this->animations_[this->currentAnimation_];

		//the current animation is defined by a string. If by mistake currentAnimation_
		//have an animation that doesn't exists, I cannot execute blitSurface because
		//there's nothing to render.
		if (!currentAnimationFrames.empty()) {
			SDL_Rect sourceRect = currentAnimationFrames[this->frameIndex_];
			graphics.blitSurface(this->spriteSheet_, &sourceRect, &destinationRectangle);
		}
	}
}
