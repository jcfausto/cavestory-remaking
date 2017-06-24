/*
 * rectangles.h
 *
 *  Created on: 15 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_RECTANGLES_H_
#define HEADERS_RECTANGLES_H_

#include "globals.h"

class Rectangle {
public:
	Rectangle() {}

	Rectangle(int x, int y, int width, int height):
		x_(x),
		y_(y),
		width_(width),
		height_(height)
	{}

	const int getCenterX() const {
		return this->x_ + this->width_ / 2;
	}

	const int getCenterY() const {
		return this->y_ + this->height_ / 2;
	}

	const int getLeft() const {
		return this->x_;
	}

	const int getRight() const {
		return this->x_ + width_;
	}

	const int getTop() const {
		return this->y_;
	}

	const int getBottom() const {
		return this->y_ + height_;
	}

	const int getWidth() const {
		return this->width_;
	}

	const int getHeight() const {
		return this->height_;
	}

	const int getSide(const sides::Side side) const {
		return
			side == sides::LEFT ? this->getLeft() :
			side == sides::RIGHT ? this->getRight() :
			side == sides::TOP ? this->getTop() :
			side == sides::BOTTOM ? this->getBottom() :
			sides::NONE;
	}

	//Takes in another Rectangle and checks if the two are colliding
	const bool collidesWith(const Rectangle &other) const {
		return
			this->getRight() >= other.getLeft() &&
			this->getLeft() <= other.getRight() &&
			this->getTop() <= other.getBottom() &&
			this->getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const {
		return (this->x_ >= 0 && this->y_ >= 0 && this->width_ >= 0 && this->height_ >= 0);
	}

	const inline Rectangle getRect() const { return *this; } //Returns a dereferenced this

private:
	int x_;
	int y_;
	int width_;
	int height_;
};



#endif /* HEADERS_RECTANGLES_H_ */
