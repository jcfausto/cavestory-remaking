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
#include "utils.h"
#include "tinyxml2.h"
#include "player.h"
#include "bat.h"

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Graphics &graphics) :
		mapName_(mapName),
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

			//TODO: Review the way I'm parsing and loading these files.
			XMLElement* pImageSource = pTileSet->FirstChildElement("image");
			const char* tmxFileTileSetPath = pImageSource->Attribute("source");
			std::string fileName = Utils::getFileNameFromFilePath(tmxFileTileSetPath);
			const std::string tileSetFilePath = globals::CONTENT_TILESETS + fileName + ".png";
			const char* source = tileSetFilePath.c_str();

			SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(source));

			pTileSet->QueryIntAttribute("firstgid", &firstGid);
			this->tileSets_.push_back(Tileset(texture, firstGid));

			//Get all the animations for that tileset
			XMLElement* pTileA = pTileSet->FirstChildElement("tile");
			if (pTileA != NULL) {
				while (pTileA) {
					AnimatedTileInfo ati;
					ati.StartTileId = pTileA->IntAttribute("id") + firstGid;
					ati.TilesetsFirstGid = firstGid;
					XMLElement* pAnimation = pTileA->FirstChildElement("animation");
					if (pAnimation != NULL) {
						while (pAnimation) {
							XMLElement* pFrame = pAnimation->FirstChildElement("frame");
							if (pFrame != NULL) {
								while (pFrame) {
									ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstGid);
									ati.Duration = pFrame->IntAttribute("duration");
									pFrame = pFrame->NextSiblingElement("frame");
								}
							}
							pAnimation = pAnimation->NextSiblingElement("animation");
						}
					}
					this->animatedTileInfos_.push_back(ati);
					pTileA = pTileA->NextSiblingElement("tile");
				}
			}

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

						//TODO: Check this logic.
						Tileset tls;
						int closest = 0;
						for (int i = 0; i < this->tileSets_.size(); i++) {
							if (this->tileSets_[i].firstGid <= gid) {
								if (this->tileSets_[i].firstGid > closest) {
										closest = this->tileSets_[i].firstGid;
										tls = this->tileSets_.at(i);
								}
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
						Vector2 finalTilesetPosition = this->getTileSetPosition(tls, gid, tileWidth, tileHeight);

						//Build the actual tile and add it to the level's tile list
						bool isAnimatedTile = false;
						AnimatedTileInfo ati;

						for (int i = 0; i < this->animatedTileInfos_.size(); i++) {
							if (this->animatedTileInfos_.at(i).StartTileId == gid) {
								ati = this->animatedTileInfos_.at(i);
								isAnimatedTile = true;
								break;
							}
						}

						if (isAnimatedTile == true) {
							std::vector<Vector2> tilesetPositions;
							for (int i = 0; i < ati.TileIds.size(); i++) {
								tilesetPositions.push_back(this->getTileSetPosition(tls, ati.TileIds.at(i), tileWidth, tileHeight));
							}

							AnimatedTile tile(tilesetPositions, ati.Duration, tls.texture,
										Vector2(tileWidth, tileHeight), finalTilePosition);
							this->animatedTileList_.push_back(tile);
						} else {
							Tile tile (tls.texture, Vector2(tileWidth, tileHeight),
										finalTilesetPosition, finalTilePosition);
							this->tileList_.push_back(tile);
						}


						tileCounter++;

						pTile = pTile->NextSiblingElement("tile");
					}
				}

				pData = pData->NextSiblingElement("data");
			}
		}

		pLayer = pLayer->NextSiblingElement("layer");
	}

	//Parse out the collisions
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");

	if (pObjectGroup != NULL) {
		while(pObjectGroup) {
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;

			if (ss.str() == "collisions") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while(pObject) {
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						this->collisionRects_.push_back(Rectangle(
								std::ceil(x) * globals::SPRITE_SCALE,
								std::ceil(y) * globals::SPRITE_SCALE,
								std::ceil(width) * globals::SPRITE_SCALE,
								std::ceil(height) * globals::SPRITE_SCALE));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//Other object groups go here with an else if (ss.str() == "whatever")
			else if (ss.str() == "spawn points") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "player") {
							this->spawnPoint_ = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
									std::ceil(y) * globals::SPRITE_SCALE);
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			} else if (ss.str() == "doors") {
				//TODO: This code is very repetitive.
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						float w = pObject->FloatAttribute("width");
						float h = pObject->FloatAttribute("height");
						Rectangle rect = Rectangle(x, y , w, h);


						XMLElement* pProperties = pObject->FirstChildElement("properties");
						if (pProperties != NULL) {
							while (pProperties) {
								XMLElement* pProperty = pProperties->FirstChildElement("property");
								if (pProperty != NULL) {
									while (pProperty) {
										const char* name = pProperty->Attribute("name");
										std::stringstream ss;
										ss << name;
										if (ss.str() == "destination") {
											const char* value = pProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											Door door = Door(rect, ss2.str());
											this->doorList_.push_back(door);
										}
										pProperty = pProperty->NextSiblingElement("property");
									}

								}
								pProperties = pProperties->NextSiblingElement("properties");
							}
						}


						if (ss.str() == "player") {
							this->spawnPoint_ = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
									std::ceil(y) * globals::SPRITE_SCALE);
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (ss.str() == "slopes") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						std::vector<Vector2> points;
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")),
								std::ceil(pObject->FloatAttribute("y")));
						XMLElement* pPolyline = pObject->FirstChildElement("polyline");
						if (pPolyline != NULL) {
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");

							std::stringstream ss;
							ss << pointString;

							Utils::split(ss.str(), pairs, ' ');
							//Now we have each of the pairs, Loop through the list of pairs
							//and split them into Vector2s and then store them in our points vector
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> ps;
								Utils::split(pairs.at(i), ps, ',');
								std::stringstream point0ss(ps.at(0));
								std::stringstream point1ss(ps.at(1));
								int p0, p1;
								point0ss>>p0;
								point1ss>>p1;
								points.push_back(Vector2(p0, p1));
							}
						}

						for (int i = 0; i < points.size(); i+=2) {
							this->slopes_.push_back(Slope(
									Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
											(p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
									Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
											(p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
							));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			} else if (ss.str() == "enemies") {
				float x, y;
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");

						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "bat") {
							this->enemies_.push_back(new Bat(graphics,
									Vector2(std::floor(x) * globals::SPRITE_SCALE,
											std::floor(y) * globals::SPRITE_SCALE)));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}

			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}

}

void Level::update(int elapsedTime, Player &player) {
	for (int i = 0; i < this->animatedTileList_.size(); i++) {
		this->animatedTileList_.at(i).update(elapsedTime);
	}

	for (int i = 0; i < this->enemies_.size(); i++) {
		this->enemies_.at(i)->update(elapsedTime, player);
	}
}

void Level::draw(Graphics &graphics) {
	for (int i = 0; i < this->tileList_.size(); i++) {
		this->tileList_.at(i).draw(graphics);
	}

	for (int i = 0; i < this->animatedTileList_.size(); i++) {
		this->animatedTileList_.at(i).draw(graphics);
	}

	for (int i = 0; i < this->enemies_.size(); i++) {
		this->enemies_.at(i)->draw(graphics);
	}
}

std::vector<Rectangle> Level::checkTileCollision(const Rectangle &other) {
	std::vector<Rectangle> others;
	for (int i = 0; i < this->collisionRects_.size(); i++) {
		if (this->collisionRects_.at(i).collidesWith(other)) {
			others.push_back(this->collisionRects_.at(i));
		}
	}
	return others;
}

const Vector2 Level::getPlayerSpawnPoint() const {
	return this->spawnPoint_;
}

//TODO: Code duplication here!
std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other) {
	std::vector<Slope> others;
	for (int i = 0; i < this->slopes_.size(); i++) {
		if (this->slopes_.at(i).collidesWith(other)) {
			others.push_back(this->slopes_.at(i));
		}
	}
	return others;
}

//TODO: All collisions are copy and paste code!
std::vector<Door> Level::checkDoorCollisions(const Rectangle &other) {
	std::vector<Door> others;
	for (int i = 0; i < this->doorList_.size(); i++) {
		if (this->doorList_.at(i).collidesWith(other)) {
			others.push_back(this->doorList_.at(i));
		}
	}
	return others;
}

//TODO: All collisions are copy and paste code! This one use pointers
std::vector<Enemy*> Level::checkEnemyCollision(const Rectangle &other) {
	std::vector<Enemy*> others;
	for (int i = 0; i < this->enemies_.size(); i++) {
		if (this->enemies_.at(i)->getBoundingBox().collidesWith(other)) {
			others.push_back(this->enemies_.at(i));
		}
	}
	return others;
}

Vector2 Level::getTileSetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
	int tilesetWidht;
	int tilesetHeight;
	SDL_QueryTexture(tls.texture, NULL, NULL, &tilesetWidht, &tilesetHeight);
	int tilesetXX = gid % (tilesetWidht / tileWidth) -1;
	tilesetXX *= tileWidth;

	int tilesetYY = 0;
	int amount = ((gid - tls.firstGid) / (tilesetWidht / tileWidth));
	tilesetYY = tileHeight * amount;

	Vector2 finalTilesetPosition = Vector2(tilesetXX, tilesetYY);
	return finalTilesetPosition;
}



