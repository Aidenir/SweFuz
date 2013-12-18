#include "SweFuzClock.h"

void FuzTime_create(FuzTime* ft, const struct tm* tim)
{

}

int GetNumLines(const struct tm* time)
{
	if(time->tm_min > 37 || time->tm_min < 23)
	{
		return 3;
	}
	if(time->tm_min > 33 || time->tm_min < 27)
	{
		return 4;		//"fem i/over halv XX"
	}
	return 2;			//"halv XX"
}