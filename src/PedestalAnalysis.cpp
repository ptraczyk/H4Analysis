#include "interface/PedestalAnalysis.hpp"
#include <assert.h>

void PedestalAnalysis::AnalyzeEvent()
{

	for (unsigned int iSample=0;iSample< l->nDigiSamples;iSample++)
	{
 		UInt_t digiChannel = l->digiChannel[iSample];
 		UInt_t digiGroup   = l->digiGroup[iSample];
 		UInt_t digiSampleIndex = l->digiSampleIndex[iSample];
 		Float_t digiSampleValue = l->digiSampleValue[iSample];
		if( digiChannel <nChannels) 
			l->FillProfile( Form("tprofile_pedestal_ch%d_HV%d",digiChannel, 0 ),digiSampleIndex +1 , digiSampleValue );
	}
	return;
}

void PedestalAnalysis::Init(LoopAndFill *l1)
{
	cout<<"[PedestalAnalysis]::[Init]"<<endl;
	BaseAnalysis::Init(l1);
	//l->BookHisto("pedestal_ch0_HV600",1024,0,1024);
	if( ! ( l1->inputBranches["digiChannel"] and 
		l1->inputBranches["digiSampleIndex"] and 
		l1->inputBranches["digiSampleValue"] ) )
		{
		cout <<"[PedestalAnalysis]::[Init]::[ERROR]: input branches are not active"<<endl;	
		cout<<"digiChannel:"<< l1->inputBranches["digiChannel"] <<endl;
		cout<<"digiSampleIndex:"<< l1->inputBranches["digiSampleIndex"] <<endl;
		cout<<"digiSampleValue:"<< l1->inputBranches["digiSampleValue"] <<endl;
		assert(0);
		}
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
