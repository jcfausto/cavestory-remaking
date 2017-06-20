/*
 * level.h
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_LEVEL_H_
#define HEADERS_LEVEL_H_

#include <string>
#include <vector>

#include "globals.h"
#include "graphics.h"
#include "tile.h"
#include "rectangles.h"
#include "slope.h"
#include "animatedtile.h"

struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);

	std::vector<Rectangle> checkTileCollision(const Rectangle &other);
	std::vector<Slope> checkSlopeCollisions(const Rectangle &other);

	const Vector2 getPlayerSpawnPoint() const;

private:
	std::string mapName_;
	Vector2 spawnPoint_;
	Vector2 size_; //The size of the entire map
	Vector2 tileSize_;

	SDL_Texture* backgroundTexture_;

	std::vector<Tile> tileList_;
	std::vector<Tileset> tileSets_;
	std::vector<Rectangle> collisionRects_;
	std::vector<Slope> slopes_;

	std::vector<AnimatedTile> animatedTileList_;
	std::vector<AnimatedTileInfo> animatedTileInfos_;


	/* void loadMap
	 * Loads a map
	 */
	void loadMap(std::string mapName, Graphics &graphics);

	Vector2 getTileSetPosition(Tileset tls, int gid, int tileWidht, int tileHeight);
};

//Tileset structure
struct Tileset {
	SDL_Texture* texture;
	int firstGid;

	Tileset() {
		this->firstGid = -1;
		this->texture = NULL;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		this->texture = texture;
		this->firstGid = firstGid;
	}
};

#endif /* HEADERS_LEVEL_H_ */
