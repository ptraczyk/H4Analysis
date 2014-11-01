#ifndef HISTOS_H
#define HISTOS_H

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"
#include <iostream>
#include "interface/Looper.hpp"
#include "interface/OutFile.hpp"

class Histos : 
	virtual public Looper, 
	virtual public OutFile
{
	map<string,TH1D*> histoContainer;
public:
	//Init & Close inheriths
	int BookHisto(string name, string title, int nBins, double xmin, double xmax);	
	void Fill(string name, double value, double weight=1);
	void Write();
};

#endif
