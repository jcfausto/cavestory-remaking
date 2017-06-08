/*
 * graphics.cpp
 *
 *  Created on: 7 de jun de 2017
 *      Author: jcfausto
 *
 *  Holds all information dealing with graphics for the game
 */

#include <SDL2/SDL.h>
#include "graphics.h"

//Constructor
Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory Remake C++");
}

//Desctructor
Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}
