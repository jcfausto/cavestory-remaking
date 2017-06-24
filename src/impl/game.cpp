/*
 * game.cpp
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 *
 *  This class holds all information for our main game loop
 */

#include <SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {}

//Every frame this method will be executed
void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event; //Will handle events

	this->level_ = Level(globals::MAPS_MAP_1, graphics);
	this->player_ = Player(graphics, this->level_.getPlayerSpawnPoint());
	this->hud_ = HUD(graphics, this->player_);


	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while(true) {
		input.beginNewFrame(); //Reset the key maps

		if (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_KEYDOWN: {
					if (event.key.repeat == 0) {
						input.keyDownEvent(event);
					}
					break;
				}
				case SDL_KEYUP: {
					input.keyUpEvent(event);
					break;
				}
				case SDL_QUIT: {
					return;
				}
				default: {
					break;
				}
			}

		}

		//Will close the window if user hits ESCAPE
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		//Will move left
		else if (input.wasKeyPressed(SDL_SCANCODE_LEFT) == true) {
			this->player_.moveLeft();
		}

		//Will move right
		else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT) == true) {
			this->player_.moveRight();
		}

		if (input.isKeyHeld(SDL_SCANCODE_UP) == true) {
			this->player_.lookUp();
		} else if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true) {
			this->player_.lookDown();
		}

		if (input.wasKeyReleased(SDL_SCANCODE_UP) == true) {
			this->player_.stopLookingUp();
		}

		if (input.wasKeyReleased(SDL_SCANCODE_DOWN) == true) {
			this->player_.stopLookingDown();
		}

		//Will jump
		if (input.wasKeyPressed(SDL_SCANCODE_Z) == true) {
			this->player_.jump();
		}


		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->player_.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME; //Stores how long this current frame took
		this->graphics_ = graphics;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	/* DRAWING ORDER
	 * 1 - Level
	 * 2 - Player
	 * 3 - The HUD
	 */
	this->level_.draw(graphics);
	this->player_.draw(graphics);
	this->hud_.drawn(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->player_.update(elapsedTime);
	this->level_.update(elapsedTime);
	this->hud_.update(elapsedTime);

	//Check collisions
	std::vector<Rectangle> others;
	others = this->level_.checkTileCollision(this->player_.getBoundingBox());

	if (others.size() > 0) {
		//Player collided with at least one tile. Handle it.
		this->player_.handleTileCollisions(others);
	}

	std::vector<Slope> otherSlopes;
	otherSlopes = this->level_.checkSlopeCollisions(this->player_.getBoundingBox());

	if (otherSlopes.size() > 0) {
		//Player collided with at least one tile. Handle it.
		this->player_.handleSlopeCollisions(otherSlopes);
	}

	//Check doors
	std::vector<Door> otherDoors;
	otherDoors = this->level_.checkDoorCollisions(this->player_.getBoundingBox());
	if (otherDoors.size() > 0) {
		this->player_.handleDoorCollision(otherDoors, this->level_, this->graphics_);
	}


}
