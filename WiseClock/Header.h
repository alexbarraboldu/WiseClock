#ifndef HEADER_H
#define HEADER_H

#include <iostream>

const int WIDTH = 20;
const int HEIGHT = 15;

struct cImage
{
	cImage(){}
	cImage(int _width, int _height, int _posX, int _posY)
	{
		width = _width;
		height = _height;
		posX = _posX;
		posY = _posY;
		image = new bool[width * height];
	}

	///	No encargarse de borrar "image" generará memory leaks

	int width, height;
	int posX, posY;
	bool* image;
};

cImage LoadImageFromFile_TXT(const char* fileName);
cImage* LoadImagesFromFile_TXT(const char* fileName);

std::ostream& operator << (std::ostream& os, const cImage& img);
cImage operator << (cImage const& objA, cImage const& objB);
cImage operator + (cImage const& objA, cImage const& objB);

#endif //!HEADER_H