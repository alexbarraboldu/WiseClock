#include "Clock.h"

Clock::Clock(const char* _clockNumbersFileName)
{
	clockNumbersFileName = _clockNumbersFileName;
	LoadClockNumbers();
	emptyScreen = cImage(WIDTH, HEIGHT, 0,0);
}

Clock::~Clock() { }

void Clock::Start()
{
	WiseClock::Start();

	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		emptyScreen.image[i] = false;
	}

	clockTime = ClockTime();

	SetClockTimeNumbersValue();
}

void Clock::Update()
{

}

void Clock::EverySecond()
{
	CalculateTime();
	CastTimeToClockNumbers();
	SetClockTimeNumbersValue();

	RenderClockNumbers();
}

///	Class functions

void Clock::LoadClockNumbers()
{
	imgClockNumbers = LoadImagesFromFile_TXT(clockNumbersFileName);
}

void Clock::RenderClockNumbers()
{
	*imgBuffer = emptyScreen << (clockTime.hour_0 +	clockTime.hour_1);
	*imgBuffer = *imgBuffer << (clockTime.dots_0);
	*imgBuffer = *imgBuffer << (clockTime.minute_0 + clockTime.minute_1);

	///	Esto controla que se renderice los segundos. Se tendría que cambiar en otro sitio, para así centrar o modificar la posición del reloj. O cambiar el canvas a renderizar.
	if (true)
	{
		*imgBuffer = *imgBuffer << (clockTime.dots_1);
		*imgBuffer = *imgBuffer << (clockTime.second_0 + clockTime.second_1);
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

void Clock::CalculateTime()
{
	///	This should add one at a time.
	///	By adding 60 we make the minutes the seconds and the hours the minutes.
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

