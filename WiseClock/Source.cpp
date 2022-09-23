#include "Header.h"
#include "Clock.h"

int main()
{
	Clock* wiseClock = new Clock("img_numbers.txt");

	wiseClock->ExecuteWiseClock();

	delete wiseClock;

	return 0;
}