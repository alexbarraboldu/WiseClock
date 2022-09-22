#include "WiseClock.h"

#include <conio.h>

WiseClock::WiseClock()
{
	imgBuffer = new cImage(WIDTH, HEIGHT, 0, 0);
	player = new cImage(0, 0, 9, 2);
}

WiseClock::~WiseClock() {
	delete[] imgBuffer->image;
	delete imgBuffer;

	delete[] player->image;
	delete player;
}

void WiseClock::ExecuteWiseClock()
{
	Start();
	EngineBase::engineLoop();
}

///	Aqu� se inicializa todo lo relacionado con el reloj.
void WiseClock::Start()
{
	///	Cargar todas las imagenes
	///		Lo m�s probable es que se tenga que crear un tipo que contenga cImage y tenga un ID (enum?)
	///		as� podremos distinguir los objetos.
	///		Se puede crear tambi�n otras clases que contengan programas a ejecutarse dentro del bucle.

	///	Asignar valores por defecto a la pantalla.
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		imgBuffer->image[i] = false;
	}

	///	MODO Juego
	///	A�adimos el suelo
	cImage ground = LoadImageFromFile_TXT("img_ground.txt");

	*imgBuffer = *imgBuffer << ground;

	*player = LoadImageFromFile_TXT("img_player.txt");
	player->posX = 9;
	player->posY = 4;

	*imgBuffer = *imgBuffer << *player;

	delete[] ground.image;
}


///	Aqu� se actualiza toda la l�gica.
/// Este Update se actualiza a 60fps (ver EngineBase constructor).
void WiseClock::Update()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 32:
			JumpPlayer();
			break;
		default:
			break;
		}
	}

}

void WiseClock::JumpPlayer()
{
	player->posY -= 2;
	*imgBuffer = *imgBuffer << *player;
}

///	Aqu� se actualiza todo lo gr�fico.
///	Este update se actualiza a 60fps (ver EngineBase constructor).
void WiseClock::Renderer()
{
	///	Limpiar pantalla	|	Se puede limpiar la pantalla de manera custom, puede que sea menos costoso
	system("cls");

	///	Dibujar la imagen final en pantalla
	int imgLength = imgBuffer->width * imgBuffer->height;
	for (size_t i = 0, j = 1; i < imgLength; i++)
	{
		if (i == imgBuffer->width * j)
		{
			++j;
			std::cout << '\n';
		}
		std::cout << imgBuffer->image[i] << ' ';
	}

	///	Dibujar el framerate
	std::cout << '\n' << FPS << '\n';

	///	Limpiar output buffer
	std::cout << std::flush;
}
