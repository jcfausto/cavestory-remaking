/*
 * hud.h
 *
 *  Created on: 23 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_HUD_H_
#define HEADERS_HUD_H_

#include "graphics.h"
#include "player.h"
#include "sprite.h"

class HUD {
public:
	HUD();
	HUD(Graphics &graphics, Player &player);

	void update(int elapsedTime);
	void drawn(Graphics &graphics);

private:
	Player player_;

	Sprite healthBarSprite_;
	Sprite healthNumver1_;
};


#endif /* HEADERS_HUD_H_ */
