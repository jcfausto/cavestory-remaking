/*
 * tile.h
 *
 *  Created on: 12 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_TILE_H_
#define HEADERS_TILE_H_

#include "graphics.h"
#include "globals.h"

struct SDL_Texture;

class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	SDL_Texture* tileset_;

	//Size of the tile
	Vector2 size_;

	//Position on the tileset where the tile is
	Vector2 tilesetPosition_;

	//Position in the map where the tile is
	Vector2 position_;
};



#endif /* HEADERS_TILE_H_ */
