#include "SweFuzClock.h"
#include <pebble.h>

#define DEBUG true


void FuzTime_create(FuzTime* ft, const struct tm* tim)
{
	SetNumLines(ft,tim);
	SetFirstLine(ft,tim);
	SetSecondLine(ft,tim);
	if (ft->lines > 2)
	{
		SetThirdLine(ft,tim);
	}
	if (ft->lines > 3)
	{
		SetFourthLine(ft,tim);
	}
	#ifdef DEBUG
  	APP_LOG(APP_LOG_LEVEL_DEBUG, "Time: %d:%d makes %d lines", tim->tm_hour,tim->tm_min,ft->lines);
  	LogFuzTime(ft);
  	#endif
}

void SetFirstLine(FuzTime* ft, const struct tm* tim)
{
	int min = tim->tm_min;
	if (min < 3 || min > 57)								//	"klockan"
	{
		strcat(ft->lineOne, strings[19]);
	}
	else if(min < 7 || min > 53 || 
			(min > 23 && min < 27) || 
			(min > 33 && min < 37) )						//	"fem"
	{
		strcat(ft->lineOne, strings[5]);
	}
	else if(min < 13 || min > 47)							//	"tio"
	{
		strcat(ft->lineOne, strings[10]);
	}
	else if(min < 17 || min > 43)							//	"kvart"
	{
		strcat(ft->lineOne,strings[15]);
	}
	else if(min < 23 || min > 37)							//	"tjugo"
	{
		strcat(ft->lineOne,strings[16]);
	}
	else if(min < 33 || min > 27)							//	"halv"
	{
		strcat(ft->lineOne,strings[14]);
	}
	else
	{
		strcat(ft->lineOne, "fail with the first line");
	}
}

void SetSecondLine(FuzTime* ft, const struct tm* tim)
{
	int min = tim->tm_min;
	if (min < 3 || min > 57)								//	"är"
	{
		strcat(ft->lineTwo,strings[20]);
	}
	else if(min < 23 || (min < 37 && min > 33))				//	"över"
	{
		strcat(ft->lineTwo, strings[18]);
	}
	else if(min < 27 && min > 23)							//	"i halv"
	{
		strcat(ft->lineTwo, strings[21]);
	}
	else if (min >37)										//	"i"
	{
		strcat(ft->lineTwo, strings[17]);
	}
	else if(min < 33 && min > 27 )							//	the hour 
	{
		strcat(ft->lineTwo, strings[tim->tm_hour + 1]);
	}
	else
	{
		strcat(ft->lineTwo, "Failed to set the second line");
	}
}

void SetThirdLine(FuzTime* ft, const struct tm* tim)
{
	int min = tim->tm_min;
	int hour = tim->tm_hour;
	if (min < 37 && min > 33)								//	"halv"
	{
		strcat(ft->lineThree, strings[14]);
	}
	else if (min < 23)										//	the hour
	{
		strcat(ft->lineThree, strings[hour]);
	}
	else if (min > 23)										//	one hour more thatn the current one
	{
		strcat(ft->lineThree, strings[hour+1]);
	}

	else
	{
		strcat(ft->lineThree, "Fail line three");
	}
}

void SetFourthLine(FuzTime* ft, const struct tm* tim)
{
	strcat(ft->lineFour,strings[tim->tm_hour + 1]);
}

void SetNumLines(FuzTime *ft, const struct tm* time)
{
	if(time->tm_min < 37 && time->tm_min > 33)
	{
		ft->lines =  4;		//"fem over halv XX"
		return;
	}
	if(time->tm_min > 33 || time->tm_min < 27)
	{
		ft->lines = 3;
		return;
	}
	ft->lines = 2;			//"halv XX"
	return;
}

void LogFuzTime(FuzTime* ft)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, ft->lineOne);
	if (ft->lines > 1)
		APP_LOG(APP_LOG_LEVEL_DEBUG, ft->lineTwo);
	if (ft->lines > 2)
		APP_LOG(APP_LOG_LEVEL_DEBUG, ft->lineThree);
	if (ft->lines > 3)
		APP_LOG(APP_LOG_LEVEL_DEBUG, ft->lineFour);
}