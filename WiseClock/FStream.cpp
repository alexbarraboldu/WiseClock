#include <iostream>
#include <fstream>

#include "Header.h"

cImage LoadImageFromFile_TXT(const char* fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::in);

	///	std::ios::good Solo retorna true si no hay ninguna otra flag activada.
	if (!file.good()) return cImage();

	///	Coger la el ancho y alto de la imagen y comprobar que el archivo sea el correcto

	///	La primera línea no puede ser más larga que 5+1 carácteres,
	/// ya que la resolución de imagen no será superior a 99x74 (4:3).
	/// Por ej.: 20;15 -> Total length 5 + 1 ('\');

	const int firstLineLength = 6;
	char firstLine[firstLineLength];
	file.getline(firstLine, firstLineLength, '\n');

	///	Comprobar que el archivo sea de una sola imagen
	if (firstLine[2] != ';') return cImage();
	///------------------

	///	Coger el ancho y alto de la imagen
	char charWidth[2] = { firstLine[0], firstLine[1] };
	int imgWidth = atoi(charWidth);

	char charHeight[2] = { firstLine[3], firstLine[4] };
	int imgHeight = atoi(charHeight);
	///------------------

	///	Coger la imagen completa
	int charImgLength = (imgWidth * imgHeight) + (1 * imgHeight);
	char* charImg = new char[charImgLength];

	///	Comprobamos que se haya leido correctamente
	//if (file.getline(charImg, charImgLength, file.eof()).bad())
	//{
	//	file.close();
	//	return new bool[2];
	//}
	file.getline(charImg, charImgLength, file.eof());
	file.close();

	int imgLength = imgWidth * imgHeight;
	cImage resultImg = cImage(imgWidth, imgHeight, 0, 0);
	resultImg.image = new bool[imgLength];

	for (size_t i = 0, j = 0, f = 1; i < imgLength; i++, j++)
	{
		resultImg.image[i] = charImg[j] - '0';
		if (i == (imgWidth * f) - 1)
		{
			++j, ++f;
		}
	}

	delete[] charImg;
	///------------------

	return resultImg;
}

cImage* LoadImagesFromFile_TXT(const char* fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::in);

	///	std::ios::good Solo retorna true si no hay ninguna otra flag activada.
	if (!file.good()) return new cImage[1];

	///	Coger la el ancho y alto de la imagen y comprobar que el archivo sea el correcto

	///	La primera línea no puede ser más larga que 5+1 carácteres,
	/// ya que la resolución de imagen no será superior a 99x74 (4:3).
	/// Por ej.: 20;15 -> Total length 5 + 1 ('\');

	const int firstLineLength = 3;
	char firstLine[firstLineLength];
	file.getline(firstLine, firstLineLength, '\n');

	///	Coger la cantidad de imagenes
	char charImgNumbers[2] = { firstLine[0], firstLine[1] };
	int imgNumbers = atoi(charImgNumbers);
	///------------------

	cImage* resultImg = new cImage[imgNumbers];

	for (size_t k = 0; k < imgNumbers; k++)
	{
		const int secondLineLength = 6;
		char secondLine[secondLineLength];
		file.getline(secondLine, secondLineLength, '\n');

		///	Coger el ancho y alto de la imagen
		char charWidth[2] = { secondLine[0], secondLine[1] };
		int imgWidth = atoi(charWidth);

		char charHeight[2] = { secondLine[3], secondLine[4] };
		int imgHeight = atoi(charHeight);
		///------------------

		///	Crear la imagen auxiliar
		int charImgLength = (imgWidth * imgHeight) + (1 * imgHeight);
		char* charImg = new char[charImgLength];

		///	Leer la imagen completa
		file.getline(charImg, charImgLength, ';');

		///	Leer una línea más porque sino se queja
		file.getline(secondLine, '\n');

		///	Inicializar valores de la imagen a leer
		int imgLength = imgWidth * imgHeight;
		resultImg[k] = cImage(imgWidth, imgHeight, 0, 0);
		
		for (size_t i = 0, j = 0, f = 1; i < imgLength; i++, j++)
		{
			resultImg[k].image[i] = charImg[j] - '0';
			if (i == (imgWidth * f) - 1)
			{
				++j, ++f;
			}
		}
		delete[] charImg;
	}

	file.close();

	///------------------

	return resultImg;
}

