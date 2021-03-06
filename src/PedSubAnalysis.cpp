#include "interface/PedSubAnalysis.hpp"

void PedSubAnalysis::ClearEvent()
{
	for(unsigned int i=0;i<MAX_DIGI_SAMPLES;++i)
		l->digiSampleValueSub[i]=0;
}

void PedSubAnalysis::AnalyzeEvent()
{
	for (unsigned int iSample=0;iSample< l->nDigiSamples;iSample++)
	{
 		UInt_t digiGroup   = l->digiGroup[iSample];
 		UInt_t digiChannel = l->digiChannel[iSample] + 8*digiGroup;
 		UInt_t digiSampleIndex = l->digiSampleIndex[iSample];
 		Float_t digiSampleValue = l->digiSampleValue[iSample];
		int hv = int(l->CeF3HV);
		Float_t valSub=0;
		if( digiChannel <unsigned(nChannels)) 
		{
		//string name=Form("tprofile_pedestal_ch%d_HV%d",digiChannel,hv);
		//float sub=pedHisto[name]->GetBinContent( digiSampleIndex +1 );
		float sub=0;
		if (pedHisto.find(pair<int,int>(digiChannel,hv)) != pedHisto.end() )
			sub=pedHisto[pair<int,int>(digiChannel,hv)]->GetBinContent( digiSampleIndex +1 );
		else
			sub=pedHisto[pair<int,int>(digiChannel,0)]->GetBinContent( digiSampleIndex +1 );
		valSub=digiSampleValue-sub;
		}
		l->digiSampleValueSub[iSample]=valSub;
		
		
	}


}

void PedSubAnalysis::Init(LoopAndFill *l1)
{
	BaseAnalysis::Init(l1);
	// check that these branches are input
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
	HV.push_back(0);
	pedHisto.clear();
	pedFile=TFile::Open(pedestalFileName.c_str());
	for( unsigned int iHV=0;iHV<HV.size() ;++iHV)
	   for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
	      {
		string name=Form("tprofile_pedestal_ch%d_HV%d",iCh,HV[iHV]);
		//pedHisto[name] = (TProfile*)pedFile->Get(name.c_str());
		pedHisto[pair<int,int>(iCh,HV[iHV])] = (TProfile*)pedFile->Get(name.c_str());
	      }
	
}

void PedSubAnalysis::Close(){
	if(pedFile!=NULL)pedFile->Close();
	pedFile=NULL;
}
