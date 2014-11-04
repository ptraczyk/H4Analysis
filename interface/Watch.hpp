#ifndef WATCH_H
#define WATCH_H

#include "TStopwatch.h"

class Watch{
protected:
	TStopwatch watch;
public:
	Watch();
	~Watch(){};
	void StartWatch();
	void StopWatch();
	double CpuTime();
	double RealTime();
};

#endif
