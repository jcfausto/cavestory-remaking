/*
 * globals.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GLOBALS_H_
#define HEADERS_GLOBALS_H_

#include <string>

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;

	const std::string ANIMATION_RUN_LEFT = "RunLeft";
	const std::string ANIMATION_RUN_RIGHT = "RunRight";

}

struct Vector2 {
	int x, y;

	Vector2() :
		x(0), y(0)
	{}

	Vector2(int x, int y) :
		x(x), y(y)
	{}

	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif /* HEADERS_GLOBALS_H_ */
