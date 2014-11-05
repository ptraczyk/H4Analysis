#ifndef PEDSUB_ANALYSIS_H
#define PEDSUB_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"

class PedSubAnalysis : public BaseAnalysis
{
/* Produce the profile histograms to do the subtraction
 *
 */
TFile *pedFile;
//map<string,TProfile*> pedHisto;
map<pair<int,int>,TProfile*> pedHisto; //ch-HV
public:
	PedSubAnalysis(){pedFile=NULL;};
	~PedSubAnalysis(){Close();};
	int nChannels;
	vector<int> HV;
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void ClearEvent();
	void AnalyzeEvent();
	void Close();
	string pedestalFileName;
};

#endif

