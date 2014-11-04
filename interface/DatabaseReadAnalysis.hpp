#ifndef PEDESTAL_ANALYSIS_H
#define PEDESTAL_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"
#include "interface/RunDBInterface.hpp"

class DatabaseReadAnalysis : public BaseAnalysis
{

public:
	DatabaseReadAnalysis(){};
	~DatabaseReadAnalysis(){};
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void AnalyzeEvent();

  RunDBInterface *mydb;
  bool loaded;

};

#endif

