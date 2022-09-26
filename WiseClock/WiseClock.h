#ifndef WISE_CLOCK_H
#define WISE_CLOCK_H

#include "ClockWiseEngine.h"
#include "Clock.h"

class WiseClock : public ClockWiseEngine
{
public:
	WiseClock();
	WiseClock(const char* _clockNumbersFileName);
	WiseClock(const char* _clockNumbersFileName, int hours, int minutes, int seconds);
	~WiseClock();

	Clock* clockProgram;

protected:
	///	Called on ExecuteWiseClock
	void Start();
	///	Called every frame
	void Update();
	void Renderer();
	///	Called every second
	void EverySecond();

};

#endif // !WISE_CLOCK_H
