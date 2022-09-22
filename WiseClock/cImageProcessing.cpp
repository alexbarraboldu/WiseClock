#include "Header.h"

///	Operador para insertar
///	Inserta objB en objA. ObjB se sobrepondrá a ObjA.
cImage operator << (cImage const& objA, cImage const& objB)
{
	cImage aux;

	aux.posY = objA.posY;
	aux.posX = objA.posX;

	aux.height = objA.height;
	aux.width = objA.width;

	int newImageLength = aux.width * aux.height;
	aux.image = new bool[newImageLength];

	int objBLength = objB.width * objB.height;

	for (size_t i = 0, j = 0, f = 1, objBf = 0; i < newImageLength; i++)
	{
		int p0B = aux.width * (objB.posY + 1 + objBf) - (aux.width - objB.posX);
		int p1B = (aux.width * (objB.posY + 1 + objBf) - (aux.width - objB.posX)) + (objB.width - 1);

		if ((i >= p0B && i <= p1B) && j < objBLength)
		{
			aux.image[i] = objB.image[j];
			++j;
			if (i == p1B) ++objBf;
		}
		else aux.image[i] = objA.image[i];

		if (i == (aux.width * f) - 1)
		{
			++f;
		}
	}

	return aux;
}

///	Operador para sumar
///	Crea una nueva matriz del tamaño de los boundaries de las dos matrices sumadas.
///	Dandole la posición que pertoca.
cImage operator + (cImage const& objA, cImage const& objB)
{
	cImage aux;

	int posY = (objA.posY <= objB.posY) ? objA.posY : objB.posY;
	int posX = (objA.posX <= objB.posX) ? objA.posX : objB.posX;

	aux.height = (posY == objA.posY) ? (objB.posY + objB.height) - posY : (objA.posY + objA.height) - posY;
	aux.width = (posX == objA.posX) ? (objB.posX + objB.width) - posX : (objA.posX + objA.width) - posX;

	int newImageLength = aux.width * aux.height;
	aux.image = new bool[newImageLength];

	int objBLength = objB.width * objB.height;
	int objALength = objA.width * objA.height;

	for (size_t i = 0, j = 0, k = 0, f = 1, objBf = 0, objAf = 0; i < newImageLength; i++)
	{
		int p0B = aux.width * ((objB.posY - posY) + 1 + objBf) - (aux.width - (objB.posX - posX));
		int p1B = (aux.width * ((objB.posY - posY) + 1 + objBf) - (aux.width - (objB.posX - posX))) + (objB.width - 1);

		int p0A = aux.width * ((objA.posY - posY) + 1 + objAf) - (aux.width - (objA.posX - posX));
		int p1A = (aux.width * ((objA.posY - posY) + 1 + objAf) - (aux.width - (objA.posX - posX))) + (objA.width - 1);

		if ((i >= p0B && i <= p1B) && j < objBLength)
		{
			aux.image[i] = objB.image[j];
			++j;
			if (i == p1B) ++objBf;
		}
		else if ((i >= p0A && i <= p1A) && k < objALength)
		{
			aux.image[i] = objA.image[k];
			++k;
			if (i == p1A) ++objAf;
		}
		else aux.image[i] = false;

		if (i == (aux.width * f) - 1) ++f;
	}

	aux.posY = posY;
	aux.posX = posX;

	return aux;
}

std::ostream& operator << (std::ostream& os, const cImage &img)
{
	os << "height: " << img.height << "\t" << "width: " << img.width << "\t" << "posX: " << img.posX << "\t" << "posY: " << img.posY << std::endl;
	
	for (size_t i = 0, j = 1; i < img.height * img.width; i++)
	{
		if (i == img.width * j)
		{
			++j;
			os << std::endl;
		}
		os << img.image[i];
	}
	os << std::endl;

	return os;
}

#pragma region TESTS
//cImage Test_AddImages(cImage a, cImage b)
//{
//	std::cout << a << std::endl;
//	std::cout << b << std::endl;
//
//	cImage c = a + b;
//
//	std::cout << c << std::endl;
//
//	return c;
//}
//
//cImage Test_InsertImage(cImage imageBase, cImage imageToInsert)
//{
//	std::cout << imageBase << std::endl;
//	std::cout << imageToInsert << std::endl;
//
//	cImage c = imageBase << imageToInsert;
//
//	std::cout << c << std::endl;
//
//	return c;
//}
#pragma endregion
