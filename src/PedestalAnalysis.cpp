#include "interface/PedestalAnalysis.hpp"
#include <assert.h>

void PedestalAnalysis::AnalyzeEvent()
{

	for (unsigned int iSample=0;iSample< l->nDigiSamples;iSample++)
		l->FillProfile( Form("tprofile_pedestal_ch%d_HV%d",l->digiChannel[iSample], 0 ), l->digiSampleIndex[iSample] +1 , l->digiSampleValue[iSample] );
	return;
}

void PedestalAnalysis::Init(LoopAndFill *l1)
{
	cout<<"[PedestalAnalysis]::[Init]"<<endl;
	BaseAnalysis::Init(l1);
	//l->BookHisto("pedestal_ch0_HV600",1024,0,1024);
	// Add 0 
	HV.push_back(0);
	for( unsigned int iHV=0;iHV<HV.size() ;++iHV)
	   {
	   for( unsigned int iCh=0;iCh<nChannels;++iCh)
	      {
		cout<<"[PedestalAnalysis]::[Init] Ch="<<iCh<<"/"<<nChannels<<" HV="<<iHV<<"/"<<HV.size() <<endl;
		l->BookHisto(Form("tprofile_pedestal_ch%d_HV%d",iCh,HV[iHV]),"Pedestal",1024,0,1024,"TProfile");
	      }	
	   }
	cout<<"[PedestalAnalysis]::[Init]::Done"<<endl;
	return ;
}
