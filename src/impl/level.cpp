/*
 * level.cpp
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "level.h"
#include "graphics.h"
#include "globals.h"
#include "tinyxml2.h"

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
		mapName_(mapName),
		spawnPoint_(spawnPoint),
		size_(Vector2(0,0)),
		backgroundTexture_(NULL)
{
	this->loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//Parse the .tmx file

	XMLDocument doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str()); //Now we have the document open

	XMLElement* mapNode = doc.FirstChildElement("map");

	//Get the width and height of the whole map and store in in size_
	int width;
	int height;

	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->size_ = Vector2(width, height);

	//Get the width and height of the tiles map and store in in tileSize_
	int tileWidth;
	int tileHeight;

	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->tileSize_ = Vector2(tileWidth, tileHeight);

	//Loading the tilesets
	XMLElement* pTileSet = mapNode->FirstChildElement("tileset");
	if (pTileSet != NULL) {
		while (pTileSet) {
			int firstGid;

			//const char* source = pTileSet->Attribute("source");
			const char* source = "content/tilesets/PrtCave.png";
			std::stringstream ss;
			ss << source; //Path to the .tsx file. Need to open the tsx and find the png path.

			SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/tilesets/PrtCave.png"));

			pTileSet->QueryIntAttribute("firstgid", &firstGid);
			this->tileSets_.push_back(Tileset(texture, firstGid));

			pTileSet = pTileSet->NextSiblingElement("tileset");
		}
	}

	//Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");

	while (pLayer != NULL) {
		//Loading the data element
		XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData != NULL) {
			while (pData) {
				//Loading the tile element
				XMLElement* pTile = pData->FirstChildElement("tile");
				if (pTile != NULL) {
					int tileCounter = 0;
					while (pTile) {
						//Build each individual tile here

						//if gid is 0, no tile should be drawn.
						if (pTile->IntAttribute("gid") == 0) {
							tileCounter++;
							if (pTile->NextSiblingElement("tile")) {
								pTile = pTile->NextSiblingElement("tile");
								continue;
							} else {
								break;
							}
						}

						//Get the tileset for this specific gid
						int gid = pTile->IntAttribute("gid");

						Tileset tls;

						for (int i = 0; i < this->tileSets_.size(); i++) {
							if (this->tileSets_[i].firstGid <= gid) {
								//This is the tileset we want
								tls = this->tileSets_.at(i);
								break;
							}
						}

						if (tls.firstGid == -1) {
							//No tileset was found for this gid
							tileCounter++;
							if (pTile->NextSiblingElement("tile")) {
								pTile = pTile->NextSiblingElement("tile");
								continue;
							} else {
								break;
							}
						}

						//Get the position of the tile in the level
						int tilePositionX = 0;
						int tilePositionY = 0;

						tilePositionX = tileCounter % width;
						tilePositionX *= tileWidth;

						tilePositionY += tileHeight * (tileCounter / width);

						Vector2 finalTilePosition = Vector2(tilePositionX, tilePositionY);

						//Calculate the position of the tile in the tileset
						int tilesetWidht;
						int tilesetHeight;
						SDL_QueryTexture(tls.texture, NULL, NULL, &tilesetWidht, &tilesetHeight);
						int tilesetXX = gid % (tilesetWidht / tileWidth) -1;
						tilesetXX *= tileWidth;

						int tilesetYY = 0;
						int amount = (gid / (tilesetWidht / tileWidth));
						tilesetYY = tileHeight * amount;

						Vector2 finalTilesetPosition = Vector2(tilesetXX, tilesetYY);

						//Build the actual tile and add it to the level's tile list
						Tile tile (tls.texture, Vector2(tileWidth, tileHeight),
								finalTilesetPosition, finalTilePosition);
						this->tileList_.push_back(tile);
						tileCounter++;

						pTile = pTile->NextSiblingElement("tile");
					}
				}

				pData = pData->NextSiblingElement("data");
			}
		}

		pLayer = pLayer->NextSiblingElement("layer");
	}

}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	for (int i = 0; i < this->tileList_.size(); i++) {
		this->tileList_.at(i).draw(graphics);
	}

	//Draw the background
	/*SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect;

	for (int x = 0; x < this->size_.x / 64; x++) {
		for (int y = 0; y < this->size_.y / 64; y++) {
			destRect.x = x * 64 * globals::SPRITE_SCALE;
			destRect.y = y * 64 * globals::SPRITE_SCALE;
			destRect.w = 64 * globals::SPRITE_SCALE;
			destRect.h = 64 * globals::SPRITE_SCALE;
			graphics.blitSurface(this->backgroundTexture_, &sourceRect, &destRect);
		}
	}*/
}



