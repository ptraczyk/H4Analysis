#define FILLER_CPP

#include "interface/Filler.hpp"
// -------------------------- TEMPLATE SPECIFICATION ----------- 
// --- VECTOR ----
void Filler::SetBranchAddress(string name, vector<unsigned int>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<unsigned int>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<int>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<int>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<float>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<float>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<double>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<double>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<bool>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<bool>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<unsigned long long>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<unsigned long long>",ptr);
	out.isFilled[name]=1;
}
// ---- VALUES ---
void Filler::SetBranchAddress(string name, unsigned int* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/i",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, unsigned long long* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/l",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, int* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/I",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, float* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/F",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, double* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/D",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
// ------------------------------------------------------------- 

void Filler::Init()
{
	fOut=TFile::Open(outFileName.c_str(),"RECREATE");
	fChain=new TChain(chainName.c_str());
	SetBranches();
}

void Filler::Close(){
	fChain->Write();
	fOut->Close();
}

void Filler::SetBranches()
{
	if ( !activeBranches.empty() )
		{
		// disable all the branches
		fChain->SetBranchStatus("*",0);
		}
	// here will be setted if in activeBranches
	SetBranchesCommon();
	SetBranchesH4tree();
	SetBranchesOuttree();
	return;
}

void Filler::SetBranchesH4tree()
{
	SetBranchAddress("runNumber"	,&out.runNumber );
	SetBranchAddress("spillNumber"	,&out.spillNumber );
	SetBranchAddress("evtNumber"	,&out.evtNumber );
	SetBranchAddress("evtTimeDist"	,&out.evtTimeDist );
	SetBranchAddress("evtTimeStart"	,&out.evtTimeStart );
	SetBranchAddress("nEvtTimes"	,&out.nEvtTimes );
	SetBranchAddress("evtTime"	,&out.evtTime[0] );
	SetBranchAddress("evtTimeBoard"	,&out.evtTimeBoard[0]);

	SetBranchAddress("nAdcChannels"	,&out.nAdcChannels);
	SetBranchAddress("adcBoard"	,&out.adcBoard[0]);
	SetBranchAddress("adcChannel"	,&out.adcChannel[0]);
	SetBranchAddress("adcData"	,&out.adcData[0]);
                                          
	SetBranchAddress("nTdcChannels"	,&out.nTdcChannels);
	SetBranchAddress("tdcBoard"	,&out.tdcBoard[0]);
	SetBranchAddress("tdcChannel"	,&out.tdcChannel[0]);
	SetBranchAddress("tdcData"	,&out.tdcData[0]);
                                         
	SetBranchAddress("nDigiSamples"	,&out.nDigiSamples);
	SetBranchAddress("digiFrequency",&out.digiFrequency[0]);
	SetBranchAddress("digiGroup"	,&out.digiGroup[0]);
	SetBranchAddress("digiChannel"	,&out.digiChannel[0]);
	SetBranchAddress("digiSampleIndex",&out.digiSampleIndex[0]);
	SetBranchAddress("digiSample"	,&out.digiSample[0]);
	SetBranchAddress("digiBoard"	,&out.digiBoard[0]);
                                          
	SetBranchAddress("nScalerWords"	,&out.nScalerWords);
	SetBranchAddress("scalerWord"	,&out.scalerWord[0]);
	SetBranchAddress("scalerBoard"	,&out.scalerBoard[0]);
                                         
	SetBranchAddress("nPatterns"	,&out.nPatterns);
	SetBranchAddress("pattern"	,&out.pattern[0]);
	SetBranchAddress("patternBoard"	,&out.patternBoard[0]);
	SetBranchAddress("patternChannel",&out.patternChannel[0]);
                                               
	SetBranchAddress("nTriggerWords",&out.nTriggerWords);
	SetBranchAddress("triggerWords"	,&out.triggerWords[0]);
	SetBranchAddress("triggerWordsBoard",&out.triggerWordsBoard[0]);

}

void Filler::SetBranchesCommon(){
	SetBranchAddress("runNumber"	,&out.runNumber);
	SetBranchAddress("spillNumber"	,&out.spillNumber);
	SetBranchAddress("evtNumber"	,&out.evtNumber);

}

void Filler::SetBranchesOuttree(){
	SetBranchAddress("ADCvalues"	,&out.ADCvalues);
	SetBranchAddress("BGOvalues"	,&out.BGOvalues);
	SetBranchAddress("SCINTvalues"	,&out.SCINTvalues);
	SetBranchAddress("TDCreco"	,&out.TDCreco  );
	SetBranchAddress("digi_charge_integrated"	,&out.digi_charge_integrated);
	SetBranchAddress("digi_max_amplitude"		,&out.digi_max_amplitude);
	SetBranchAddress("digi_pedestal"		,&out.digi_pedestal);
	SetBranchAddress("digi_pedestal_rms"		,&out.digi_pedestal_rms);
	SetBranchAddress("digi_time_at_frac30"		,&out.digi_time_at_frac30);
	SetBranchAddress("digi_time_at_frac50"		,&out.digi_time_at_frac50);
	SetBranchAddress("digi_time_at_max"		,&out.digi_time_at_max);
	SetBranchAddress("HODOX1",&out.HODOX1   );
	SetBranchAddress("HODOX2",&out.HODOX2   );
	SetBranchAddress("HODOY1",&out.HODOY1   );
	SetBranchAddress("HODOY2",&out.HODOY2   );
}

bool Filler::isActive(string name)
{
	map<string,bool>::iterator it;
	it=activeBranches.find(name);
	if (it == activeBranches.end() ) return false;
	else return activeBranches[name];
}

