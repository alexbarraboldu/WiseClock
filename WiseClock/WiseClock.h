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

	cImage* player;

private:
	void Start();
	void Update() override;
	void Renderer();

	void JumpPlayer();
};

#endif // !WISE_CLOCK_H
