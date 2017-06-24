/*
 * bat.cpp
 *
 *  Created on: 24 de jun de 2017
 *      Author: jcfausto
 */

#include "graphics.h"
#include "globals.h"
#include "player.h"
#include "bat.h"

Bat::Bat() {}

Bat::Bat(Graphics &graphics, Vector2 spawnPoint) :
	Enemy(graphics, globals::CONTENT_SPRITES_NPCCEMET, 32, 32, 16, 16, spawnPoint, 140),
	startingX_(spawnPoint.x),
	startingY_(spawnPoint.y),
	shouldMoveUp_(false)
{
	this->setupAnimations();
	this->playAnimation(globals::BAT_ANIMATION_FLY_LEFT);
}

void Bat::update(int elapsedTime, Player &player) {
	this->direction_ = player.getX() > this->x_ ? RIGHT : LEFT;
	this->playAnimation(this->direction_ == RIGHT ? globals::BAT_ANIMATION_FLY_RIGHT :
			globals::BAT_ANIMATION_FLY_LEFT);

	//Move up or down
	this->y_ += this->shouldMoveUp_ ? -globals::BAT_ANIMATION_VERTICAL_STEP :
			globals::BAT_ANIMATION_VERTICAL_STEP;

	if (this->y_ > (this->startingY_ + globals::BAT_ANIMATION_VERTICAL_MOVEMENT_RANGE) ||
			this->y_ < this->startingY_ - globals::BAT_ANIMATION_VERTICAL_MOVEMENT_RANGE) {
		this->shouldMoveUp_ = !this->shouldMoveUp_;
	}

	Enemy::update(elapsedTime, player);
}

void Bat::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}

void Bat::animationDone(std::string currentAnimation) {

}

void Bat::setupAnimations() {
	this->addAnimation(3, 2, 32, globals::BAT_ANIMATION_FLY_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(3, 2, 48, globals::BAT_ANIMATION_FLY_RIGHT, 16, 16, Vector2(0,0));
}

void Bat::touchPlayer(Player* player) {
	player->gainHealth(globals::BAT_DAMAGE_VALUE);
}
