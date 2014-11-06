#ifndef PEDSUB_ANALYSIS_H
#define PEDSUB_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"

#include "TSpline.h"
#include "TF1.h"

class Corr1Analysis : public BaseAnalysis
{
/* Produce the profile histograms to do the subtraction
 *
 */
TFile *maxAmplFile;
TFile *chIntFile;

// this splines are inverted !!!
vector<TSpline*> maxAmplSpls;
vector<TSpline*> chIntSpls;

vector<TF1*> maxAmplLines;
vector<TF1*> chIntLines;

public:
	Corr1Analysis(){ 
			maxAmplFile=NULL;
			chIntFile=NULL; 
			chIntFileName="data/chintCorr1.root";
			maxAmplFileName="data/chintCorr1.root";
			};
	~Corr1Analysis(){Close();};
	int nChannels;
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void ClearEvent();
	void AnalyzeEvent();
	void Close();
	string maxAmplFileName;
	string chIntFileName;
	// spl must be inverted
	static double CorrType1(double y,TSpline *spl,TF1 *line);
};

#endif

