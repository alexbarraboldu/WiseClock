#include "Clock.h"

Clock::Clock(const char* clockNumbersFileName)
{
	LoadClockNumbers(clockNumbersFileName);

	clockImgBuffer = new cImage(WIDTH, HEIGHT, 0, 0);
	emptyScreen = cImage(WIDTH, HEIGHT, 0, 0);

	startClock = true;
	currentClockMode = ClockMode::SYSTEM_CLOCK;
}

Clock::Clock(const char* clockNumbersFileName, int _hours, int _minutes, int _seconds)
{
	LoadClockNumbers(clockNumbersFileName);

	clockImgBuffer = new cImage(WIDTH, HEIGHT, 0, 0);
	emptyScreen = cImage(WIDTH, HEIGHT, 0, 0);

	startClock = true;
	currentClockMode = ClockMode::SYSTEM_CLOCK;

	SetTime(_hours, _minutes, _seconds);
}

Clock::~Clock() { }

void Clock::OnStart()
{
	///	Asignar valores por defecto a la pantalla.
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		clockImgBuffer->image[i] = false;
	}

	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		emptyScreen.image[i] = false;
	}
	///-------------------------------------------

	clockTime = ClockTime();

	SetClockTimeNumbersValue();
}

//void Clock::Update()
//{
//
//}

void Clock::OnEverySecond()
{
	CalculateTime();
	CastTimeToClockNumbers();
	SetClockTimeNumbersValue();

	RenderClockNumbers();
}

cImage* Clock::OnRender()
{
	return clockImgBuffer;
}

///	Class functions

void Clock::LoadClockNumbers(const char* clockNumbersFileName)
{
	imgClockNumbers = LoadImagesFromFile_TXT(clockNumbersFileName);
}

void Clock::RenderClockNumbers()
{
	*clockImgBuffer = emptyScreen << (clockTime.hour_0 +	clockTime.hour_1);
	*clockImgBuffer = *clockImgBuffer << (clockTime.dots_0);
	*clockImgBuffer = *clockImgBuffer << (clockTime.minute_0 + clockTime.minute_1);

	///	Esto controla que se renderice los segundos. Se tendría que cambiar en otro sitio, para así centrar o modificar la posición del reloj. O cambiar el canvas a renderizar.
	if (true)
	{
		*clockImgBuffer = *clockImgBuffer << (clockTime.dots_1);
		*clockImgBuffer = *clockImgBuffer << (clockTime.second_0 + clockTime.second_1);
	}
}

void Clock::SetClockTimeNumbersPosition()
{
	clockTime.hour_0.posX = 1;
	clockTime.hour_0.posY = 1;

	clockTime.hour_1.posX = 5;
	clockTime.hour_1.posY = 1;

	clockTime.dots_0.posX = 8;
	clockTime.dots_0.posY = 1;

	clockTime.minute_0.posX = 11;
	clockTime.minute_0.posY = 1;

	clockTime.minute_1.posX = 15;
	clockTime.minute_1.posY = 1;

	clockTime.dots_1.posX = 18;
	clockTime.dots_1.posY = 1;

	clockTime.second_0.posX = 21;
	clockTime.second_0.posY = 1;

	clockTime.second_1.posX = 25;
	clockTime.second_1.posY = 1;

}

void Clock::SetClockTimeNumbersValue()
{
	clockTime.hour_0	= imgClockNumbers[(int)currentClockNumbers[0]];
	clockTime.hour_1	= imgClockNumbers[(int)currentClockNumbers[1]];
	clockTime.dots_0	= imgClockNumbers[(int)currentClockNumbers[2]];
	clockTime.minute_0	= imgClockNumbers[(int)currentClockNumbers[3]];
	clockTime.minute_1	= imgClockNumbers[(int)currentClockNumbers[4]];
	clockTime.dots_1	= imgClockNumbers[(int)currentClockNumbers[2]];
	clockTime.second_0	= imgClockNumbers[(int)currentClockNumbers[5]];
	clockTime.second_1	= imgClockNumbers[(int)currentClockNumbers[6]];

	SetClockTimeNumbersPosition();
}

void Clock::CastTimeToClockNumbers()
{
	int firstHourDigit = hours % 10;
	int secondHourDigit = (hours / 10) % 10;

	int firstMinuteDigit = minutes % 10;
	int secondMinuteDigit = (minutes / 10) % 10;

	int firstSecondDigit = seconds % 10;
	int secondSecondDigit = (seconds / 10) % 10;

	currentClockNumbers[0] = (ClockNumbers)secondHourDigit;
	currentClockNumbers[1] = (ClockNumbers)firstHourDigit;
	currentClockNumbers[2] = ClockNumbers::DOTS;
	currentClockNumbers[3] = (ClockNumbers)secondMinuteDigit;
	currentClockNumbers[4] = (ClockNumbers)firstMinuteDigit;
	currentClockNumbers[5] = (ClockNumbers)secondSecondDigit;
	currentClockNumbers[6] = (ClockNumbers)firstSecondDigit;
}

///	Clock Program

void Clock::CalculateTime()
{
	if (!startClock) return;

	switch (currentClockMode)
	{
	case SYSTEM_CLOCK:
		SystemClockMode();
		break;
	case STOP_WATCH:
		StopWatchMode();
		break;
	case TIMER:
		TimerMode();
		break;
	default:
		break;
	}
}

void Clock::StopWatchMode()
{
	++seconds;

	if (seconds > 59)
	{
		seconds = 0;
		++minutes;

		if (minutes > 59)
		{
			minutes = 0;
			++hours;

			if (hours > 23)
			{
				hours = 0;
			}
		}
	}
}

void Clock::TimerMode()
{
	--seconds;

	if (seconds < 0)
	{
		seconds = 59;
		--minutes;

		if (minutes < 0)
		{
			minutes = 59;
			--hours;

			if (hours < 0)
			{
				StartStop();
			}
		}
	}
}

void Clock::SystemClockMode()
{
	time_t now;
	time(&now);

	tm l;
	localtime_s(&l, &now);

	hours = l.tm_hour;
	minutes = l.tm_min;
	seconds = l.tm_sec;
}

///	Public class functions

void Clock::SetTime(int _hours, int _minutes, int _seconds)
{
	hours = _hours;
	minutes = _minutes;
	seconds = _seconds;
}

void Clock::StartStop()
{
	startClock = !startClock;
}

void Clock::Reset()
{
	startClock = false;
	SetTime(0, 0, 0);
}

void Clock::SetClockType(ClockMode newClockMode)
{
	currentClockMode = newClockMode;
}

void Clock::ChooseClockType()
{
	std::cout << "Press a number to change clock mode:\n"
			<< "1: System Clock\n"
			<< "2: Timer\n"
			<< "3: Stop Watch"
			<< std::endl;

	int c = getchar();
	switch (c)
	{
	case 49:			//	1
		Reset();
		SetClockType(ClockMode::SYSTEM_CLOCK);
		StartStop();
		break;
	case 50:			//	2
		Reset();
		SetClockType(ClockMode::TIMER);
		///	Permitir introducir fecha
		InputDate();
		break;
	case 51:			//	3
		Reset();
		SetClockType(ClockMode::STOP_WATCH);
		///	Permitir introducir fecha
		InputDate();
		break;
	default:
		break;
	}
}

void Clock::InputDate()
{
	char date[9];

	std::cout << "Introduce the date as the next format hh/mm/ss: " << std::endl;
	std::cin.clear();
	std::cin.sync();
	std::cin >> date;

	char individualDate[2];

	individualDate[0] = date[0];
	individualDate[1] = date[1];
	hours = atoi(individualDate);


	individualDate[0] = date[3];
	individualDate[1] = date[4];
	minutes = atoi(individualDate);

	individualDate[0] = date[6];
	individualDate[1] = date[7];
	seconds = atoi(individualDate);
}

