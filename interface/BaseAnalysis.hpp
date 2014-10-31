#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

// -- fwd declared
class Looper;

class BaseAnalysis{
	Looper  *l;
public:
	virtual void Loop();
};

#include "interface/Looper.hpp"

#endif
