#ifndef CLOCK_WISE_ENGINE_H
#define CLOCK_WISE_ENGINE_H

#include "EngineBase.h"
#include "Header.h"

class ClockWiseEngine : public EngineBase
{
public:
	ClockWiseEngine();
	~ClockWiseEngine();

	void ExecuteWiseClock();

	cImage* imgBuffer;


protected:
	///	Called on ExecuteWiseClock
	virtual void Start() = 0;
	///	Called every frame
	virtual void Update() = 0;
	virtual void Renderer();
	///	Called every second
	virtual void EverySecond() = 0;
};

#endif // !CLOCK_WISE_ENGINE_H
