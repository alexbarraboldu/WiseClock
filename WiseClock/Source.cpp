#include "Header.h"
#include "WiseClock.h"


int main()
{
	WiseClock* wiseClock = new WiseClock("img_numbers.txt", 10, 14, 50);

	wiseClock->ExecuteWiseClock();

	delete wiseClock;

	return 0;
}