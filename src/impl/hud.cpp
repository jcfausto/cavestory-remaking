/*
 * hud.cpp
 *
 *  Created on: 23 de jun de 2017
 *      Author: jcfausto
 */

#include "hud.h"
#include "graphics.h"
#include "player.h"

HUD::HUD() {}

HUD::HUD(Graphics &graphics, Player &player) {
	this->player_ = player;
	this->healthBarSprite_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 40, 64, 8, 35, 70);
	this->healthNumver1_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 56, 8, 8, 66, 70);
}

void HUD::update(int elapsedTime) {
	this->healthNumver1_.setSourceRectangleX(globals::SPRITE_TEXTBOX_NUMBER_PIXEL_WIDTH * this->player_.getCurrentHealth());
}

void HUD::drawn(Graphics &graphics) {
	this->healthBarSprite_.draw(graphics, this->healthBarSprite_.getX(), this->healthBarSprite_.getY());
	this->healthNumver1_.draw(graphics, this->healthNumver1_.getX(), this->healthNumver1_.getY());
}


