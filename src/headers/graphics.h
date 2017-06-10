/*
 * graphics.h
 *
 *  Created on: 7 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GRAPHICS_H_
#define HEADERS_GRAPHICS_H_

#include <SDL2/SDL.h>
#include <map>
#include <string>


//By declaring this struct, I am able to not
//include the SDL headers here and delay this
//inclusion to the implementation file
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics(); //Constructor
	~Graphics(); //Destructor

	/* SDL_Surface* loadImage
	 * Loads an image into the spriteSheets_ map if it doesn't already exist
	 * As a result, each image will only ever be loaded once
	 * Returns the image from the map regardless of whether or not it was loaded
	 */
	SDL_Surface* loadImage(const std::string &filePath);

	/* void blitSurface
	 * Draws a texture to a certain part of the screen
	 * sourceRectangle and destinationRectangle is where in the screen we'll be drawing
	 */
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
	 * Renders everything to the screen
	 */
	void flip();

	/* void clear
	 * Clears the screen
	 */
	void clear();

	/* SDL_Renderer* getRenderer
	 * Returns the renderer
	 */
	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	//This map will hold in memory every sprite sheets we use during the game
	std::map<std::string, SDL_Surface*> spriteSheets_;
};


#endif /* HEADERS_GRAPHICS_H_ */
