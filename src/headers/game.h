/*
 * game.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GAME_H_
#define HEADERS_GAME_H_

#include "player.h"
#include "level.h"
#include "graphics.h"
#include "hud.h"

class Game {
	public:
		Game(); //Constructor
		~Game(); //Destructor
	private:

		//This is the main game loop
		void gameLoop();

		/* void draw
		 * Draw the new frame on the screen
		 */
		void draw(Graphics &graphics);


		/* void update
		 * Each time a new frame starts, this method will be called
		 */
		void update(float elapsedTime);

		/* player_
		 * Represents the player
		 */
		Player player_;

		/* level_
		 * Represents the current level
		 */
		Level level_;

		/* hud_
		 * HUD displaying game information
		 */
		HUD hud_;
};

#endif /* HEADERS_GAME_H_ */
