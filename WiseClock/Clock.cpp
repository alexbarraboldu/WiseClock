#include "Clock.h"

Clock::Clock(const char* _clockNumbersFileName)
{
	clockNumbersFileName = _clockNumbersFileName;
	//numbers = _numbers;
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
	SetClockTimeNumbersPosition();
}

void Clock::Update()
{
}
void Clock::EverySecond()
{
	++clockIterator;

	if (clockIterator > numbers)
	{
		clockIterator = 0;
	}

	RenderClockNumbers(clockIterator);
}

///	Class functions

void Clock::LoadClockNumbers()
{
	clockNumbers = LoadImagesFromFile_TXT(clockNumbersFileName);
}

void Clock::RenderClockNumbers(int i)
{
	*imgBuffer = emptyScreen << (clockTime.hour_0 +	clockTime.hour_1);
	*imgBuffer = *imgBuffer << (clockTime.dots);
	*imgBuffer = *imgBuffer << (clockTime.minute_0 + clockTime.minute_1);
}

cImage Clock::GetClockNumber(ClockNumbers clockNumber)
{
	return clockNumbers[int(clockNumber)];
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

void Clock::SetClockTimeNumbersValue(ClockNumbers* arr)
{
	///	Se tiene que implementar la lógica para llamar a esta función.
	///	Se puede hacer luego que solo se actualice según el valor que cambia.
	/// Puede que esto último esté relacionado con el RenderClockNumbers;

	//clockTime.hour_0 = GetClockNumber(arr[0]);
	//clockTime.hour_1 = GetClockNumber(arr[1]);
	//clockTime.dots = GetClockNumber(arr[2]);
	//clockTime.minute_0 = GetClockNumber(arr[3]);
	//clockTime.minute_1 = GetClockNumber(arr[4]);

	clockTime.hour_0 = GetClockNumber(ClockNumbers::ONE);
	clockTime.hour_1 = GetClockNumber(ClockNumbers::EIGHT);
	clockTime.dots = GetClockNumber(ClockNumbers::DOTS);
	clockTime.minute_0 = GetClockNumber(ClockNumbers::TWO);
	clockTime.minute_1 = GetClockNumber(ClockNumbers::THREE);
}

