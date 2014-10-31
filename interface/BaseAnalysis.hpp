#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

// -- fwd declared
class Looper;

class BaseAnalysis{
	Looper  *l;
public:
	BaseAnalysis(){};
	~BaseAnalysis(){};
	virtual inline void Init(Looper*l1) { l = l1 ; };
	virtual void Loop();
};

#include "interface/Looper.hpp"

#endif
