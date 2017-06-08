/*
 * input.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_INPUT_H_
#define HEADERS_INPUT_H_

#include <SDL2/SDL.h>
#include <map>

class Input {
public:
	//This function will be called at the begining of every new frame
	void beginNewFrame();

	//Key handling routines
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);
	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);


private:
	//This maps will hold which keys are currently being held by the user
	std::map<SDL_Scancode, bool> heldKeys_;

	//This maps will hold which keys are being pressed by the user
	std::map<SDL_Scancode, bool> pressedKeys_;

	//This maps will hold which keys were released by the user
	std::map<SDL_Scancode, bool> releasedKeys_;
};



#endif /* HEADERS_INPUT_H_ */
