/*
 * player.cpp
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#include "player.h"
#include "graphics.h"
#include "globals.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player(){}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, globals::CONTENT_SPRITES_MYCHAR, 0, 0, 16, 16, x, y, 100)
{
	graphics.loadImage(globals::CONTENT_SPRITES_MYCHAR);
	this->setupAnimations();
	this->playAnimation(globals::ANIMATION_RUN_RIGHT);
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, globals::ANIMATION_IDLE_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 0, 16, globals::ANIMATION_IDLE_RIGHT, 16, 16, Vector2(0,0));
	this->addAnimation(3, 0, 0, globals::ANIMATION_RUN_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(3, 0, 16, globals::ANIMATION_RUN_RIGHT, 16, 16, Vector2(0,0));
}


void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->x_, this->y_);
}

/* MOVING FUNCTIONS */

void Player::moveLeft() {
	this->dx_ = -player_constants::WALK_SPEED;
	this->playAnimation(globals::ANIMATION_RUN_LEFT);
	this->facing_ = LEFT;
}

void Player::moveRight() {
	this->dx_ = player_constants::WALK_SPEED;
	this->playAnimation(globals::ANIMATION_RUN_RIGHT);
	this->facing_ = RIGHT;
}

void Player::stopMoving() {
	this->dx_ = 0; //Don't want to move.
	this->playAnimation(this->facing_ == LEFT ? globals::ANIMATION_IDLE_LEFT : globals::ANIMATION_IDLE_RIGHT);
}

void Player::animationDone(std::string currentAnimation) {}

void Player::update(float elapsedTime) {
	this->x_ += this->dx_ * elapsedTime; //This is what actually will move the character on the screen
	AnimatedSprite::update(elapsedTime);
}

