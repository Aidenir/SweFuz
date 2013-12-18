/**
	The actual clock stuff. Functions for turning time 
	into fuzzy strings
*/
#include <time.h>

#define lineSize 8		//Longest string is 7 so I guess the eight is \0 or something?

typedef struct FuzTime
{
	int lines;		//How many lines the current time requires
	char 	lineOne[lineSize],
			lineTwo[lineSize],
			lineThree[lineSize],
			lineFour[lineSize];
}FuzTime;

///The strings which are used
// static const char* strings[] = {
//     "tolv",
//     "ett",
//     "två",
//     "tre",
//     "fyra",
//     "fem",
//     "sex",
//     "sju",
//     "åtta",
//     "nio",
//     "tio",
//     "elva",
//     "tolv",
//     "ett",
//     "halv",
//     "kvart",
//     "tjugo",
//     "i",
//     "över",
//     "klockan",
//     "är",
//     "i halv"
// };
static const char* strings[] = {
    "tolv", "ett", "tva", "tre", "fyra", "fem", "sex", "sju", "atta", "nio", "tio", "elva", "tolv", "ett", "halv", "kvart", "tjugo", "i", "over", "klockan", "ar","i halv"};



///Takes a tm struct and fills the members with the correct data
void FuzTime_create(FuzTime* ft, const struct tm* tim);

///Sets the string for the first line
void SetFirstLine(FuzTime* ft, const struct tm* tim);
///Sets the string for the second line
void SetSecondLine(FuzTime* ft, const struct tm* tim);
///Sets the string for the third line
void SetThirdLine(FuzTime* ft, const struct tm* tim);
///Sets the string for the fourth line
void SetFourthLine(FuzTime* ft, const struct tm* tim);

///Decides how many lines must be used for the specified time
void SetNumLines(FuzTime* ft, const struct tm* time);

///Prints the fuztime struct lines to the log
void LogFuzTime(FuzTime* ft);
