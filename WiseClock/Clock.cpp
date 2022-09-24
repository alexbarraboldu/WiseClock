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
	*imgBuffer = *imgBuffer << (clockTime.dots);
	*imgBuffer = *imgBuffer << (clockTime.minute_0 + clockTime.minute_1);
}

void Clock::SetClockTimeNumbersPosition()
{
	clockTime.hour_0.posX = 1;
	clockTime.hour_0.posY = 1;

	clockTime.hour_1.posX = 5;
	clockTime.hour_1.posY = 1;

	clockTime.dots.posX = 8;
	clockTime.dots.posY = 1;

	clockTime.minute_0.posX = 11;
	clockTime.minute_0.posY = 1;

	clockTime.minute_1.posX = 15;
	clockTime.minute_1.posY = 1;
}

void Clock::SetClockTimeNumbersValue()
{
	///	Se tiene que implementar la lógica para llamar a esta función.
	///	Se puede hacer luego que solo se actualice según el valor que cambia.
	/// Puede que esto último esté relacionado con el RenderClockNumbers;

	clockTime.hour_0	= imgClockNumbers[(int)currentClockNumbers[0]];
	clockTime.hour_1	= imgClockNumbers[(int)currentClockNumbers[1]];
	clockTime.dots		= imgClockNumbers[(int)currentClockNumbers[2]];
	clockTime.minute_0	= imgClockNumbers[(int)currentClockNumbers[3]];
	clockTime.minute_1	= imgClockNumbers[(int)currentClockNumbers[4]];

	SetClockTimeNumbersPosition();
}

void Clock::CastTimeToClockNumbers()
{
	int firstHourDigit = hours % 10;
	int secondHourDigit = (hours / 10) % 10;

	int firstMinuteDigit = minutes % 10;
	int secondMinuteDigit = (minutes / 10) % 10;

	currentClockNumbers[0] = (ClockNumbers)secondHourDigit;
	currentClockNumbers[1] = (ClockNumbers)firstHourDigit;
	currentClockNumbers[2] = ClockNumbers::DOTS;
	currentClockNumbers[3] = (ClockNumbers)secondMinuteDigit;
	currentClockNumbers[4] = (ClockNumbers)firstMinuteDigit;
}

void Clock::CalculateTime()
{
	///	This should add one at a time.
	///	By adding 60 we make the minutes the seconds and the hours the minutes.
	seconds += 60;

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

