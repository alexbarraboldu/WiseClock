#ifndef WISE_CLOCK_H
#define WISE_CLOCK_H

#include "EngineBase.h"
#include "Header.h"

class WiseClock : EngineBase
{
public:
	WiseClock();
	~WiseClock();

	void ExecuteWiseClock();

	cImage* imgBuffer;


private:
	///	Called on ExecuteWiseClock
	virtual void Start() = 0;
	///	Called every frame
	virtual void Update() = 0;
	virtual void Renderer();

};

#endif // !WISE_CLOCK_H
