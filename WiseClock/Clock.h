#include "WiseClock.h"

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

	cImage dots_0;

	cImage minute_0;
	cImage minute_1;

	cImage dots_1;

	cImage second_0;
	cImage second_1;
};

///	He de separar esta classe de WiseClock,
///	para as� poder ejecutarla cuando quiera desde la aplicaci�n WiseClock.
/// 
/// A�adirle seguridad al leer el archivo de digitos.
/// Pasar el archivo de digitos a binario.
/// 
/// Solventar los memory leaks.
/// 
/// Crear StopWatch()
/// Crear Timer()
/// Crear SystemClock()
/// 
/// Crear men� para escoger entre esas 3 opciones.
/// 
/// Cada opci�n del programa Clock, tendr� su men� o accesos directos.
/// Por ej.: En StopWatch() deber�as poder parar, reanudar, crear vueltas y reiniciar el reloj.
/// Por ej.: En Timer() deber�as poder setear el tiempo, pararlo, reanudarlo y reiniciarlo.
/// Por ej.: En SystemClock() deber�as poder setear el tiempo tu mismo y poner el del sistema.
/// 
/// Puede que estos modos de Clock se tengan que hacer como clases derivadas.
/// As� Clock tiene un men� suyo, cada modo tiene su men� y todos los modos pueden volver al modo original.
/// 

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

	int hours;
	int minutes;
	int seconds;

	cImage emptyScreen;
	cImage* imgClockNumbers;

	ClockTime clockTime;
	ClockNumbers currentClockNumbers[7];

	void LoadClockNumbers();
	void SetClockTimeNumbersPosition();

	void CalculateTime();
	void CastTimeToClockNumbers();
	void SetClockTimeNumbersValue();
	void RenderClockNumbers();
};