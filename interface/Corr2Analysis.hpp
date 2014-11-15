#ifndef PEDSUB_ANALYSIS_H
#define PEDSUB_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"

#include "TSpline.h"
#include "TF1.h"
#include "TStopwatch.h"

class Corr2Analysis : public BaseAnalysis
{
/* Produce the profile histograms to do the subtraction
 *
 */
vector<TH1D*> myhistos;
	//solve non-linear equation -- tg method=very fast
	double solve(double m , double q , double A ,double tau,double x=100,double epsilon=0.0001,int iteration=0);
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
	TH1D *log(TH1D*h);
#ifdef VERBOSE_CORR2
	TStopwatch mywatch;
	void DrawLine(float x1,float y1, float x2,float y2);
#endif
};

#endif

