#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

#include "interface/Watch.hpp"

// -- fwd declared
class LoopAndFill;

class BaseAnalysis: public Watch {
protected:
	LoopAndFill  *l;
public:
	BaseAnalysis(){};
	~BaseAnalysis(){};
	virtual void Init(LoopAndFill*l1); // { l = l1 ; };
	virtual void Loop();
	virtual void AnalyzeEvent();
	virtual void ClearEvent(){}; // clear  all the output it is going to fill
};

#include "interface/LooperAndFiller.hpp"

#endif
