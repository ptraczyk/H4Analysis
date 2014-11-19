#ifndef PEDESTAL_ANALYSIS_H
#define PEDESTAL_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"
#include "interface/Waveform.hpp"
#include <algorithm>
#include <map>

#define wcXl 0
#define wcXr 1
#define wcYd 3
#define wcYu 2

#define nFibersHodo 64
#define nBGOChannels 24
#define nSCINTChannels 4

class mcpAnalysis : public BaseAnalysis
{

public:
	mcpAnalysis(){};
	~mcpAnalysis(){};
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void AnalyzeEvent();

  std::map<unsigned int,unsigned int> mapdigichannels;
  std::vector<Waveform*> waveform;
  float timeSampleUnit(int drs4Freq);

};

#endif

