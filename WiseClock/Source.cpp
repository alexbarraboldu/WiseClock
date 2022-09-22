#include "Header.h"
#include "WiseClock.h"

int main()
{
	WiseClock* wiseClock = new WiseClock();

	wiseClock->ExecuteWiseClock();

	delete wiseClock;

	return 0;
}