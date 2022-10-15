
#include <windows.h>

#include <ceng/lib/timerlib.h>

double Ceng_HighPrecisionTimer()
{
	LARGE_INTEGER ticks_sec;
	LARGE_INTEGER ticks;
	double result;
	double ticksec;
	double tickcount;
		
	QueryPerformanceFrequency(&ticks_sec);
	QueryPerformanceCounter(&ticks);
		
	tickcount = ticks.QuadPart;
	ticksec = ticks_sec.QuadPart;
	result = tickcount/ticksec;
	return result;
}
	
void Ceng_HighPrecisionWait(double seconds)
{
	double starttime;
	double time;
	
	starttime = Ceng_HighPrecisionTimer();
	do
	{
		time = Ceng_HighPrecisionTimer();
	}while(time <= starttime+seconds);
}

