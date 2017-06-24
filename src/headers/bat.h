/*
 * bat.h
 *
 *  Created on: 24 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_BAT_H_
#define HEADERS_BAT_H_

#include "enemy.h"

class Bat : public Enemy {
public:
	Bat();
	Bat(Graphics &graphics, Vector2 spawnPoint);

	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);
	void touchPlayer(Player* player);

	void animationDone(std::string currentAnimation);
	void setupAnimations();

private:
	float startingX_;
	float startingY_;
	bool shouldMoveUp_;
};

#endif /* HEADERS_BAT_H_ */
