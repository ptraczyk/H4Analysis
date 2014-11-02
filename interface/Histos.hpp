#ifndef HISTOS_H
#define HISTOS_H

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"
#include "TProfile.h"
#include <iostream>
#include "interface/Looper.hpp"
#include "interface/OutFile.hpp"

class Histos : 
	virtual public Looper, 
	virtual public OutFile
{
	map<string,TH1*> histoContainer;
public:
	//Init & Close inheriths
	int BookHisto(string name, string title, int nBins, double xmin, double xmax,string type="TH1D");	
	void FillHisto(string name, double value, double weight=1);
	void FillProfile(string name, double x,double y, double weight=1);
	void Write();
	// TODO, add a check if exist, so it will not be created
	TH1D* GetHisto(string name){return (TH1D*)histoContainer[name];}
};

#endif
