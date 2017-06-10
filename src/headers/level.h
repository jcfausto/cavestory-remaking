/*
 * level.h
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_LEVEL_H_
#define HEADERS_LEVEL_H_

#include <string>
#include "globals.h"
#include "graphics.h"

struct SDL_Texture;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);

private:
	std::string mapName_;
	Vector2 spawnPoint_;
	Vector2 size_; //The size of the entire map

	SDL_Texture* backgroundTexture_;

	/* void loadMap
	 * Loads a map
	 */
	void loadMap(std::string mapName, Graphics &graphics);
};



#endif /* HEADERS_LEVEL_H_ */
