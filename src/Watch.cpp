#include "interface/Watch.hpp"
void Watch::StartWatch()
{
	watch.Start(kFALSE);
}
void Watch::StopWatch()
{
	watch.Stop();
}

double Watch::CpuTime(){
	return watch.CpuTime();
}
double Watch::RealTime(){
	return watch.RealTime();
}
Watch::Watch()
{
	watch.Reset();
}
