#ifndef PLOT_ANALYSIS_H
#define PLOT_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"

class PlotAnalysis : public BaseAnalysis
{
/* Produce the profile histograms to do the subtraction
 *
 */
public:
	PlotAnalysis(){};
	~PlotAnalysis(){};
	int nChannels;
	//vector<int> HV;
	vector<int> E;
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void AnalyzeEvent();
};

#endif

