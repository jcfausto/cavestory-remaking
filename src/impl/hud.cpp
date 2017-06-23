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
	this->healthNumber1_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 56, 8, 8, 66, 70);
	this->currentHealthBar_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 25, 39, 5, 83, 72);
	this->lvWord_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 81, 81, 11, 7, 38, 55);
	this->lvNumber_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 56, 8, 8, 66, 52);
	this->expBar_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 0, 72, 40, 8, 83, 52);
	this->slash_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 72, 48, 8, 8, 100, 36);
	this->dashes_ = Sprite(graphics, globals::CONTENT_SPRITES_TEXTBOX, 81, 51, 15, 11, 132, 26);
}

void HUD::update(int elapsedTime) {
	this->healthNumber1_.setSourceRectangleX(globals::SPRITE_TEXTBOX_NUMBER_PIXEL_WIDTH * this->player_.getCurrentHealth());

	//Calculate the width of current health bar
	float currentHealthBarWidth = (globals::SPRITE_TEXTBOX_CURRENT_HEALTH_BAR_WIDTH * this->player_.getCurrentHealth()) / this->player_.getMaxHealth();

	this->currentHealthBar_.setSourceRectangleW(currentHealthBarWidth);
}

//TODO: Can this be drawn from a list of Sprites?
void HUD::drawn(Graphics &graphics) {
	this->healthBarSprite_.draw(graphics, this->healthBarSprite_.getX(), this->healthBarSprite_.getY());
	this->healthNumber1_.draw(graphics, this->healthNumber1_.getX(), this->healthNumber1_.getY());
	this->currentHealthBar_.draw(graphics, this->currentHealthBar_.getX(), this->currentHealthBar_.getY());
	this->lvWord_.draw(graphics, this->lvWord_.getX(), this->lvWord_.getY());
	this->lvNumber_.draw(graphics, this->lvNumber_.getX(), this->lvNumber_.getY());
	this->expBar_.draw(graphics, this->expBar_.getX(), this->expBar_.getY());
	this->slash_.draw(graphics, this->slash_.getX(), this->slash_.getY());
	this->dashes_.draw(graphics, this->dashes_.getX(), this->dashes_.getY());
}


