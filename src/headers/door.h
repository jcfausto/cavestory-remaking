/*
 * door.h
 *
 *  Created on: 24 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_DOOR_H_
#define HEADERS_DOOR_H_

#include <string>
#include "rectangles.h"
#include "globals.h"

class Door : public Rectangle {
public:
	Door();
	Door(Rectangle rect, std::string destination);

	const inline Rectangle getRectantle() const { return this->getRectantle(); }
	const inline std::string getDestination() const { return this->destination_; }
private:
	std::string destination_;
};



#endif /* HEADERS_DOOR_H_ */
