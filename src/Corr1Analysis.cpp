#include "interface/Corr1Analysis.hpp"

#include "TMath.h"
#include "TGraph.h"

double Corr1Analysis::CorrType1(double y,TSpline *spl,TF1 *line)
{
	//Corrections are in Log/Log
	double Y=TMath::Log(y);
	// find x tc spl(x)==y
	double x=spl->Eval(Y);
	// y'=line(x)
	double Y1=line->Eval(x);
	// return y'
	return TMath::Exp(Y1);
}

void Corr1Analysis::ClearEvent()
{
	l->digi_charge_integrated_corr1->clear();
	l->digi_max_amplitude_corr1->clear();
}

void Corr1Analysis::AnalyzeEvent()
{

	for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
	      {
		l->digi_charge_integrated_corr1->push_back(CorrType1( 
			  (*l->digi_charge_integrated_sub)[iCh],
			  chIntSpls[iCh],
			  chIntLines[iCh]
			  ));
		l->digi_max_amplitude_corr1->push_back(CorrType1(
			(*l->digi_max_amplitude_sub)[iCh],
			maxAmplSpls[iCh],
			maxAmplLines[iCh]
			));
		}

}

void Corr1Analysis::Init(LoopAndFill *l1)
{
	BaseAnalysis::Init(l1);
	// check that these branches are input

	chIntFile=TFile::Open(chIntFileName.c_str());
	maxAmplFile=TFile::Open(maxAmplFileName.c_str());
	double x,y;

	for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
	      {
		string gName=Form("tofit_ch%d",iCh);
		string lName=Form("line_ch%d",iCh);
	
		// Get Graphs and convert to splines	
		TGraph *orig=(TGraph*)maxAmplFile->Get(gName.c_str());
		TGraph *invert=new TGraph();
			for(int i=0;i<orig->GetN();++i)
				{
				orig->GetPoint(i,x,y);
				invert->SetPoint(i,y,x);
				}
		maxAmplSpls.push_back( new TSpline3(Form("ma_spline_%d",iCh), invert  ) );
		orig=(TGraph*) chIntFile->Get(gName.c_str());
		invert->Delete();
		invert= new TGraph(); // add Delete ? 
			for(int i=0;i<orig->GetN();++i)
				{
				orig->GetPoint(i,x,y);
				invert->SetPoint(i,y,x);
				}
		chIntSpls.push_back( new TSpline3(Form("ci_spline_%d",iCh), invert   )  );
		//Get Lines
		maxAmplLines.push_back( (TF1*)maxAmplFile->Get(lName.c_str())->Clone( Form("ma_%s",lName.c_str())))  ;
		chIntLines.push_back  ( (TF1*)chIntFile->Get(lName.c_str())->Clone(Form("ci_%s",lName.c_str())))  ;
		
	      }
	
}

void Corr1Analysis::Close(){
	if(maxAmplFile!=NULL)maxAmplFile->Close();
	maxAmplFile=NULL;
	if(chIntFile!=NULL)chIntFile->Close();
	chIntFile=NULL;
}
