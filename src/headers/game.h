/*
 * game.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GAME_H_
#define HEADERS_GAME_H_

#include "player.h"
#include "graphics.h"

class Game {
	public:
		Game(); //Constructor
		~Game(); //Destructor
	private:

		//This is the main game loop
		void gameLoop();

		//This is the method for drawing on the screen
		void draw(Graphics &graphics);

		//This is the method for framing update
		void update(float elapsedTime);

		Player player_;
};

#endif /* HEADERS_GAME_H_ */
