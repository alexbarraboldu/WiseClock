#include "WiseClock.h"

///	Coordenadas para poner los números donde tocan
///	Y=3;X=2		-> Para la izq.
///	Y=3;X=11	-> Para la der.
///	Y=3;x9		-> Para los puntos.

class Clock : public WiseClock
{
public:

	Clock(const char* _clockNumbersFileName);
	~Clock();

	void Start() override;
	void Update() override;

private:

	const char* clockNumbersFileName;
	const int numbers = 11;
	cImage* clockNumbers;

	cImage emptyScreen;

	void LoadClockNumbers();
	void RenderClockNumbers();
};