#include "WiseClock.h"

///	Coordenadas para poner los números donde tocan
///	Y=0;X=2		-> Para la izq.
///	Y=0;X=6		-> Para la der.
///	Y=0;x9		-> Para los puntos.

///	He de añadir 5 imagenes a emptyScreen
///	De izquierda a derecha.
/// Luego mirar optimizaciones.

enum ClockNumbers
{
	ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOTS
};

struct ClockTime
{
	ClockTime()
	{}

	cImage hour_0;
	cImage hour_1;

	cImage dots;

	cImage minute_0;
	cImage minute_1;
};

class Clock : public WiseClock
{
public:

	Clock(const char* _clockNumbersFileName);
	~Clock();

	void Start() override;
	void Update() override;

	void EverySecond() override;

private:

	const char* clockNumbersFileName;
	const int numbers = 11;

	cImage* clockNumbers;
	cImage emptyScreen;
	ClockTime clockTime;

	int clockIterator;

	void LoadClockNumbers();
	void RenderClockNumbers(int i);
	cImage GetClockNumber(ClockNumbers clockNumber);
	void SetClockTimeNumbersPosition();
	void SetClockTimeNumbersValue(ClockNumbers* arr = new ClockNumbers());
};