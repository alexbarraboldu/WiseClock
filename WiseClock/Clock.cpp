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
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		emptyScreen.image[i] = false;
	}
}

void Clock::Update()
{
	RenderClockNumbers();
}

///	Class functions

void Clock::LoadClockNumbers()
{
	clockNumbers = LoadImagesFromFile_TXT(clockNumbersFileName);
}

void Clock::RenderClockNumbers()
{
	cImage auxImg;
	for (size_t i = 0; i < numbers; i++)
	{
		 auxImg = emptyScreen << clockNumbers[0];
	}
	auxImg = emptyScreen;
	imgBuffer = &auxImg;
}
