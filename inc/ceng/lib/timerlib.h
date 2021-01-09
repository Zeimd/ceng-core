#ifndef TIMER_H
#define TIMER_H

extern "C"
{
	double Ceng_HighPrecisionTimer();
	void Ceng_HighPrecisionWait(double seconds);
}

#endif