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

	int hours;
	int minutes;
	int seconds;

	cImage emptyScreen;
	cImage* imgClockNumbers;

	ClockTime clockTime;
	ClockNumbers currentClockNumbers[5];

	void LoadClockNumbers();
	void SetClockTimeNumbersPosition();

	void CalculateTime();
	void CastTimeToClockNumbers();
	void SetClockTimeNumbersValue();
	void RenderClockNumbers();
};