/*
 * door.cpp
 *
 *  Created on: 24 de jun de 2017
 *      Author: jcfausto
 */

#include <string>
#include "rectangles.h"
#include "globals.h"
#include "door.h"

Door::Door() {};

Door::Door(Rectangle rect, std::string destination) :
		Rectangle(rect.getLeft() * globals::SPRITE_SCALE, rect.getTop() * globals::SPRITE_SCALE,
					rect.getWidth() * globals::SPRITE_SCALE, rect.getHeight() * globals::SPRITE_SCALE),
		destination_(destination)
{};



