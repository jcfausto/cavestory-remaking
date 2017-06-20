/*
 * utils.h
 *
 *  Created on: 17 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_UTILS_H_
#define HEADERS_UTILS_H_

#include <string>
#include <iostream>

class Utils {
public:

	/* unsigned int split
	 * split a string <txt> everywhere a certain character <ch> is found
	 * store the resulting substrings in a vector <strs>
	 * return the size of the vector
	 */
	static unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch) {
		int pos = txt.find(ch);
		int initialPos = 0;
		strs.clear();

		while (pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
			initialPos = pos + 1;
			pos = txt.find(ch, initialPos);
		}
		strs.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));

		return strs.size();
	}

	/* std::string getFileNameFromFilePath(const std::string filePath)
	 * In this case, all files will have conventional names that only contains one "."
	 * There's not need to pass for all different path representations.
	 */
	static std::string getFileNameFromFilePath(const std::string &filePath) {
		std::size_t found = filePath.find_last_of("/\\");
		std::string fileName = filePath.substr(found+1);
		found = fileName.find_last_of(".");
		fileName = fileName.substr(0,found);
		return found != std::string::npos ? fileName : globals::UNKNOWN_FILENAME;
	}
};



#endif /* HEADERS_UTILS_H_ */
