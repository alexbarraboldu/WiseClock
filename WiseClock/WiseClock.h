#ifndef WISE_CLOCK_H
#define WISE_CLOCK_H

#include "EngineBase.h"
#include "Header.h"

///	Coordenadas para poner los números donde tocan
///	Y=3;X=2		-> Para la izq.
///	Y=3;X=11	-> Para la der.
///	Y=3;x9		-> Para los puntos.

class WiseClock : EngineBase
{
public:
	WiseClock();
	~WiseClock();

	void ExecuteWiseClock();

	cImage* imgBuffer;


private:
	void Start();
	void Update() override;
	void Renderer();

};

#endif // !WISE_CLOCK_H
