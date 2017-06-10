/*
 * sprite.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 *
 *  Base class for sprites
 */

#ifndef HEADERS_SPRITE_H_
#define HEADERS_SPRITE_H_

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
			int width, int height, float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);

protected:
	SDL_Rect sourceRectangle_;
	SDL_Texture* spriteSheet_;

	float x_, y_;
private:
};

#endif /* HEADERS_SPRITE_H_ */
