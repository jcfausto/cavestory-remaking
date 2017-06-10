/*
 * player.h
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_PLAYER_H_
#define HEADERS_PLAYER_H_

#include "graphics.h"
#include "animatedsprite.h"
#include "globals.h"

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, float x, float y);

	void draw(Graphics &grapics);
	void update(float elapsedTime);

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();


	/* MOVING FUNCTIONS */

	/* void moveLeft
	 * Moves the player left by -dx_
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx_
	 */
	void moveRight();

	/* void stopMoving
	 * Stops moving the player
	 */
	void stopMoving();

private:
	//Delta of the change in the x and y positions.
	float dx_, dy_;

	//Current player's facing direction
	Direction facing_;
};


#endif /* HEADERS_PLAYER_H_ */
