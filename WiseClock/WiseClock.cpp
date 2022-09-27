#include "WiseClock.h"

#include <conio.h>

WiseClock::WiseClock()
{
	clockProgram = nullptr;
}

WiseClock::WiseClock(const char* _clockNumbersFileName)
{
	clockProgram = new Clock(_clockNumbersFileName);
}

WiseClock::WiseClock(const char* _clockNumbersFileName, int hours, int minutes, int seconds)
{
	clockProgram = new Clock(_clockNumbersFileName, hours, minutes, seconds);
}

WiseClock::~WiseClock()
{
	delete clockProgram;
}


///	Aquí se inicializa todo lo relacionado con el reloj.
void WiseClock::Start()
{
	ClockWiseEngine::Start();
	///	MODO Clock
	clockProgram->OnStart();
}


///	Aquí se actualiza toda la lógica.
/// Este Update se actualiza a 60fps (ver EngineBase constructor).
/// 
/// Crear una función virtual que se llame InputHandler() y vaya aquí, así los programas
/// puestos podrán manejar input independientemente
void WiseClock::Update()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 27:			///	ESC
			ExitEngine();
			break;
		case 13:			///	Enter
			clockProgram->StartStop();
			break;
		case 8:				///	Backspace
			clockProgram->Reset();
		case 32:			///	Spacebar
			clockProgram->ChooseClockType();
		default:
			break;
		}
	}

}

///	Aquí se actualiza todo lo gráfico.
///	Este update se actualiza a 60fps (ver EngineBase constructor).
void WiseClock::Renderer()
{
	ClockWiseEngine::Renderer();

	imgBuffer = clockProgram->OnRender();
}

void WiseClock::EverySecond()
{
	clockProgram->OnEverySecond();
}
