/*
 * input.cpp
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 *
 *  Keeps track of keyboards state
 */

#include "input.h"

//This function gets called at the beginning of each new frame
//to reset the keys that are no longer relevant
void Input::beginNewFrame() {
	this->pressedKeys_.clear();
	this->releasedKeys_.clear();
}

//This gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	this->pressedKeys_[event.key.keysym.scancode] = true;
	this->heldKeys_[event.key.keysym.scancode] = true;
}

//This gets called when a key is released
void Input::keyUpEvent(const SDL_Event& event) {
	this->releasedKeys_[event.key.keysym.scancode] = true;
	this->heldKeys_[event.key.keysym.scancode] = false;
}

//Check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->pressedKeys_[key];
}

//Check if a certain key was released during the current frame
bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->releasedKeys_[key];
}

//Check if a certain key is currently being held during the current frame
bool Input::isKeyHeld(SDL_Scancode key) {
	return this->heldKeys_[key];
}



