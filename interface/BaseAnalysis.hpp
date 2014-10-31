#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

// -- fwd declared
class Looper;

class BaseAnalysis{
	Looper  *l;
public:
	BaseAnalysis(){};
	~BaseAnalysis(){};
	virtual void Init(Looper*l1); // { l = l1 ; };
	virtual void Loop();
	virtual void AnalyzeEvent();
};

#include "interface/Looper.hpp"

#endif
