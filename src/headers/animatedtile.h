/*
 * animatedtile.h
 *
 *  Created on: 20 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_ANIMATEDTILE_H_
#define HEADERS_ANIMATEDTILE_H_

#include <vector>
#include "tile.h"
#include "globals.h"

class AnimatedTile : Tile {
public:
	AnimatedTile(std::vector<Vector2> tilsetPosition, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	int amountOfTime = 0;
	bool notDone = false;
private:
	std::vector<Vector2> tilesetPositions_;
	int tileToDraw_;
	int duration_;
};

struct AnimatedTileInfo {
public:
	int TilesetsFirstGid;
	int StartTileId;
	std::vector<int> TileIds;
	int Duration;
};

#endif /* HEADERS_ANIMATEDTILE_H_ */
