#ifndef CLOCK_PROGRAM_H
#define CLOCK_PROGRAM_H

enum ClockNumbers
{
	ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOTS
};

bool** clock_numbers;

bool* GetClockNumber(ClockNumbers clockNumber)
{
	return clock_numbers[int(clockNumber)];
}

#endif // !CLOCK_PROGRAM_H
