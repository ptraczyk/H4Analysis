#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

// -- fwd declared
class LoopAndFill;

class BaseAnalysis{
protected:
	LoopAndFill  *l;
public:
	BaseAnalysis(){};
	~BaseAnalysis(){};
	virtual void Init(LoopAndFill*l1); // { l = l1 ; };
	virtual void Loop();
	virtual void AnalyzeEvent();
};

#include "interface/LooperAndFiller.hpp"

#endif
