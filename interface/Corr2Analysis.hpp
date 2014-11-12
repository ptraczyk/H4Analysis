#ifndef PEDSUB_ANALYSIS_H
#define PEDSUB_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"

#include "TSpline.h"
#include "TF1.h"

class Corr2Analysis : public BaseAnalysis
{
/* Produce the profile histograms to do the subtraction
 *
 */
vector<TH1D*> myhistos;
	//solve non-linear equation -- tg method=very fast
	double solve(double m , double q , double A ,double tau,double x=100,double epsilon=0.0001);
public:
	Corr2Analysis()	{tolerance=0.05;};
	~Corr2Analysis(){Close();};
	int nChannels;
	float tolerance;
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void ClearEvent();
	void AnalyzeEvent();
	void Close();
	void getHistos();
	void resetHistos();
	pair<double,double> fit(TH1D*h);
};

#endif

