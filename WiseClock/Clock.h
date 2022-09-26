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
///	para así poder ejecutarla cuando quiera desde la aplicación WiseClock.
/// 
/// Añadirle seguridad al leer el archivo de digitos.
/// Pasar el archivo de digitos a binario.
/// 
/// Solventar los memory leaks.
/// 
/// Crear StopWatch()
/// Crear Timer()
/// Crear SystemClock()
/// 
/// Crear menú para escoger entre esas 3 opciones.
/// 
/// Cada opción del programa Clock, tendrá su menú o accesos directos.
/// Por ej.: En StopWatch() deberías poder parar, reanudar, crear vueltas y reiniciar el reloj.
/// Por ej.: En Timer() deberías poder setear el tiempo, pararlo, reanudarlo y reiniciarlo.
/// Por ej.: En SystemClock() deberías poder setear el tiempo tu mismo y poner el del sistema.
/// 
/// Puede que estos modos de Clock se tengan que hacer como clases derivadas.
/// Así Clock tiene un menú suyo, cada modo tiene su menú y todos los modos pueden volver al modo original.
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