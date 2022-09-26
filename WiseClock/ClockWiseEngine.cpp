#include "ClockWiseEngine.h"

//#include <conio.h>

ClockWiseEngine::ClockWiseEngine()
{
	imgBuffer = new cImage(WIDTH, HEIGHT, 0, 0);
}

ClockWiseEngine::~ClockWiseEngine() {
	delete[] imgBuffer->image;
	delete imgBuffer;

}

void ClockWiseEngine::ExecuteWiseClock()
{
	Start();
	EngineBase::engineLoop();
}

///	Aquí se inicializa todo lo relacionado con el reloj.
void ClockWiseEngine::Start()
{
	///	Asignar valores por defecto a la pantalla.
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		imgBuffer->image[i] = false;
	}
}


///	Aquí se actualiza toda la lógica.
/// Este Update se actualiza a 60fps (ver EngineBase constructor).
//void ClockWiseEngine::Update()
//{
//	if (_kbhit())
//	{
//		switch (_getch())
//		{
//		case 32:
//			ExitEngine();
//			break;
//		default:
//			break;
//		}
//	}
//
//}

///	Aquí se actualiza todo lo gráfico.
///	Este update se actualiza a 60fps (ver EngineBase constructor).
void ClockWiseEngine::Renderer()
{
	///	Limpiar pantalla	|	Se puede limpiar la pantalla de manera custom, puede que sea menos costoso
	system("cls");

	///	Dibujar la imagen final en pantalla
	int imgLength = imgBuffer->width * imgBuffer->height;
	char charToPrint = ' ';
	for (size_t i = 0, j = 1; i < imgLength; i++)
	{
		if (i == imgBuffer->width * j)
		{
			++j;
			std::cout << '\n';
		}

		if (imgBuffer->image[i]) charToPrint = 'O';
		else charToPrint = ' ';
		std::cout << charToPrint << ' ';
	}

	///	Dibujar el framerate
	std::cout << '\n' << FPS << '\n';

	///	Limpiar output buffer
	//std::cout << std::flush;
}
