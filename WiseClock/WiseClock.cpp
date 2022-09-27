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


///	Aqu� se inicializa todo lo relacionado con el reloj.
void WiseClock::Start()
{
	ClockWiseEngine::Start();
	///	MODO Clock
	clockProgram->OnStart();
}


///	Aqu� se actualiza toda la l�gica.
/// Este Update se actualiza a 60fps (ver EngineBase constructor).
/// 
/// Crear una funci�n virtual que se llame InputHandler() y vaya aqu�, as� los programas
/// puestos podr�n manejar input independientemente
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

///	Aqu� se actualiza todo lo gr�fico.
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
