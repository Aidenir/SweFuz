/**
	The actual clock stuff. Functions for turning time 
	into fuzzy strings
*/
#include <time.h>

#define lineSize 5

typedef struct FuzTime
{
	int lines;		//How many lines the current time requires
	char 	lineOne[lineSize],
			lineTwo[lineSize],
			lineThree[lineSize],
			lineFour[lineSize];
}FuzTime;

///Takes a tm struct and fills the members with the correct data
void FuzTime_create(FuzTime* ft, const struct tm* tim);

///Decides how many lines must be used for the specified time
int GetNumLines(const struct tm* time);
