/*
 * graphics.h
 *
 *  Created on: 7 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GRAPHICS_H_
#define HEADERS_GRAPHICS_H_

//By declaring this struct, I am able to not
//include the SDL headers here and delay this
//inclusion to the implementation file
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics(); //Constructor
	~Graphics(); //Destructor
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};


#endif /* HEADERS_GRAPHICS_H_ */
