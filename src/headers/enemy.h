/*
 * enemy.h
 *
 *  Created on: 24 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_ENEMY_H_
#define HEADERS_ENEMY_H_

#include <string>
#include "animatedsprite.h"
#include "globals.h"

class Player;

class Graphics;

class Enemy : public AnimatedSprite {
public:
	Enemy();
	virtual ~Enemy();
	Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY,
			int width, int height, Vector2 spawnPoint, int timeToUpdate);

	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics);

	/* virtual void touchPlayer
	 * whatever happen the player touch the enemy this function will be called
	 */
	virtual void touchPlayer(Player* player) = 0;

	//TODO: Common characteristic with player
	const inline int getMaxHealth() const { return this->maxHealth_; }
	const inline int getCurrentHealth() const { return this->currentHealth_; }

protected:
	Direction direction_;

private:
	int maxHealth_;
	int currentHealth_;
};


#endif /* HEADERS_ENEMY_H_ */
