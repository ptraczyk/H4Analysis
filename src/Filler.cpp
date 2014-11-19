#define FILLER_CPP

#include "interface/Filler.hpp"
// -------------------------- TEMPLATE SPECIFICATION ----------- 
// --- VECTOR ----
void Filler::SetBranchAddress(string name, vector<unsigned int>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<unsigned int>"<<endl;
	//(*ptr) = new vector<unsigned int>();
	fChain->Branch(name.c_str(),"vector<unsigned int>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<int>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<int>"<<endl;
	//(*ptr) = new vector<int>();
	fChain->Branch(name.c_str(),"vector<int>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<float>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<float>"<<endl;
	//(*ptr) = new vector<float>();
	fChain->Branch(name.c_str(),"vector<float>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<double>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<double>"<<endl;
	//(*ptr) = new vector<double>();
	fChain->Branch(name.c_str(),"vector<double>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<bool>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<bool>"<<endl;
	//(*ptr) = new vector<bool>();
	fChain->Branch(name.c_str(),"vector<bool>",ptr);	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, vector<unsigned long long>** ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type vector<unsigned long long>"<<endl;
	//(*ptr) = new vector<unsigned long long>();
	fChain->Branch(name.c_str(),"vector<unsigned long long>",ptr);
	out.isFilled[name]=1;
}
// ---- VALUES ---
void Filler::SetBranchAddress(string name, unsigned int* ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type uint"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s/i",name.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, unsigned long long* ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type u long long"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s/l",name.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, int* ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type int"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s/I",name.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, float* ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type float"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s/F",name.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchAddress(string name, double* ptr)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchAddress]Setting address for branch "<<name<<" with type double"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s/D",name.c_str()));	
	out.isFilled[name]=1;
}
// ------------------------------------------------------------- 
// ---- ARRAYS ---
void Filler::SetBranchArray(string name, unsigned int* ptr,string n)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchArray]Setting address for branch "<<name<<" with type uint"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s[%s]/i",name.c_str(),n.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchArray(string name, unsigned long long* ptr,string n)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchArray]Setting address for branch "<<name<<" with type u long long"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s[%s]/l",name.c_str(),n.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchArray(string name, int* ptr,string n)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchArray]Setting address for branch "<<name<<" with type int"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s[%s]/I",name.c_str(),n.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchArray(string name, float* ptr,string n)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchArray]Setting address for branch "<<name<<" with type float"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s[%s]/F",name.c_str(),n.c_str()));	
	out.isFilled[name]=1;
}
void Filler::SetBranchArray(string name, double* ptr,string n)
{
	if (!isActive(name) ) return;
	cout<<"[Filler]::[SetBranchArray]Setting address for branch "<<name<<" with type double"<<endl;
	fChain->Branch(name.c_str(),ptr,Form("%s[%s]/D",name.c_str(),n.c_str()));	
	out.isFilled[name]=1;
}

void Filler::Init()
{
	//fOut=TFile::Open(outFileName.c_str(),"RECREATE");
	OutFile::Init();
	fOut->cd();
	cout<<"[Filler]::[Init]:Creating tree with name: "<<outTreeName<<endl;
	fChain=new TTree(outTreeName.c_str(),outTreeName.c_str());
	SetBranches();
}

void Filler::Write(){
	cout<<"[Filler]::[Write] Tree "<<endl;
	fOut->cd();
	fChain->Print();
	fChain->Write();
	//fOut->Close();
}

void Filler::SetBranches()
{
	if ( !activeBranches.empty() )
		{
		// disable all the branches
		//fChain->SetBranchStatus("*",0);
		}
	// here will be setted if in activeBranches
	SetBranchesCommon();
	SetBranchesH4tree();
	SetBranchesOuttree();
	return;
}

void Filler::SetBranchesH4tree()
{
	//SetBranchAddress("runNumber"	,&out.runNumber );
	//SetBranchAddress("spillNumber"	,&out.spillNumber );
	//SetBranchAddress("evtNumber"	,&out.evtNumber );
	SetBranchAddress("evtTimeDist"	,&out.evtTimeDist );
	SetBranchAddress("evtTimeStart"	,&out.evtTimeStart );
	SetBranchAddress("nEvtTimes"	,&out.nEvtTimes );
	SetBranchArray("evtTime"	,&out.evtTime[0] 	,"nEvtTimes");
	SetBranchArray("evtTimeBoard"	,&out.evtTimeBoard[0]	,"nEvtTimes");

	SetBranchAddress("nAdcChannels"	,&out.nAdcChannels);
	SetBranchArray("adcBoard"	,&out.adcBoard[0]	,"nAdcChannels");
	SetBranchArray("adcChannel"	,&out.adcChannel[0]	,"nAdcChannels");
	SetBranchArray("adcData"	,&out.adcData[0]	,"nAdcChannels");
                                          
	SetBranchAddress("nTdcChannels"	,&out.nTdcChannels);
	SetBranchArray("tdcBoard"	,&out.tdcBoard[0]	,"nTdcChannels");
	SetBranchArray("tdcChannel"	,&out.tdcChannel[0]	,"nTdcChannels");
	SetBranchArray("tdcData"	,&out.tdcData[0]	,"nTdcChannels");
                                         
	SetBranchAddress("nDigiSamples"	,&out.nDigiSamples);
	SetBranchArray("digiFrequency",&out.digiFrequency[0]	,"nDigiSamples");
	SetBranchArray("digiGroup"	,&out.digiGroup[0]	,"nDigiSamples");
	SetBranchArray("digiChannel"	,&out.digiChannel[0]	,"nDigiSamples");
	SetBranchArray("digiSampleIndex"	,&out.digiSampleIndex[0],"nDigiSamples");
	SetBranchArray("digiSampleValue"	,&out.digiSampleValue[0],"nDigiSamples");
	SetBranchArray("digiSampleValueSub"	,&out.digiSampleValueSub[0],"nDigiSamples");
	SetBranchArray("digiBoard"	,&out.digiBoard[0]	,"nDigiSamples");
                                          
	SetBranchAddress("nScalerWords"	,&out.nScalerWords);
	SetBranchArray("scalerWord"	,&out.scalerWord[0]	,"nScalerWords");
	SetBranchArray("scalerBoard"	,&out.scalerBoard[0]	,"nScalerWords");
                                         
	SetBranchAddress("nPatterns"	,&out.nPatterns);
	SetBranchArray("pattern"	,&out.pattern[0]	,"nPatterns");
	SetBranchArray("patternBoard"	,&out.patternBoard[0]	,"nPatterns");
	SetBranchArray("patternChannel",&out.patternChannel[0]	,"nPatterns");
                                               
	SetBranchAddress("nTriggerWords",&out.nTriggerWords);
	SetBranchArray("triggerWords"	,&out.triggerWords[0]	,"nTriggerWords");
	SetBranchArray("triggerWordsBoard",&out.triggerWordsBoard[0],"nTriggerWords");


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
	SetBranchAddress("digi_SeePulse_Index"		,&out.digi_SeePulse_Index);
	SetBranchAddress("digi_SeePulse_Value"		,&out.digi_SeePulse_Value);
	SetBranchAddress("digi_Mib2Pulse_Index"		,&out.digi_Mib2Pulse_Index);
	SetBranchAddress("digi_Mib2Pulse_Value"		,&out.digi_Mib2Pulse_Value);
	SetBranchAddress("digi_Mib3Pulse_Index"		,&out.digi_Mib3Pulse_Index);
	SetBranchAddress("digi_Mib3Pulse_Value"		,&out.digi_Mib3Pulse_Value);
	SetBranchAddress("digi_Zstak1Pulse_Index"		,&out.digi_Zstak1Pulse_Index);
	SetBranchAddress("digi_Zstak1Pulse_Value"		,&out.digi_Zstak1Pulse_Value);
	SetBranchAddress("digi_Zstak2Pulse_Index"		,&out.digi_Zstak2Pulse_Index);
	SetBranchAddress("digi_Zstak2Pulse_Value"		,&out.digi_Zstak2Pulse_Value);
	SetBranchAddress("digi_pedestal"		,&out.digi_pedestal);
	SetBranchAddress("digi_pedestal_rms"		,&out.digi_pedestal_rms);
	SetBranchAddress("digi_time_at_frac30"		,&out.digi_time_at_frac30);
	SetBranchAddress("digi_time_at_frac50"		,&out.digi_time_at_frac50);
	SetBranchAddress("digi_time_at_max"		,&out.digi_time_at_max);
	SetBranchAddress("HODOX1",&out.HODOX1   );
	SetBranchAddress("HODOX2",&out.HODOX2   );
	SetBranchAddress("HODOY1",&out.HODOY1   );
	SetBranchAddress("HODOY2",&out.HODOY2   );

	SetBranchAddress("TableX",&out.TableX);
	SetBranchAddress("TableY",&out.TableY);
	SetBranchAddress("CeF3HV",&out.CeF3HV);
	SetBranchAddress("BGOHV",&out.BGOHV);
	SetBranchAddress("BeamEnergy",&out.BeamEnergy);
	SetBranchAddress("BeamTilt",&out.BeamTilt);
	SetBranchAddress("IsPhysics",&out.IsPhysics);

	SetBranchAddress("digi_charge_integrated_sub"	,&out.digi_charge_integrated_sub);
	SetBranchAddress("digi_max_amplitude_sub"	,&out.digi_max_amplitude_sub);
	SetBranchAddress("digi_pedestal_sub"		,&out.digi_pedestal_sub);
	SetBranchAddress("digi_pedestal_rms_sub"	,&out.digi_pedestal_rms_sub);

	SetBranchAddress("digi_charge_integrated_corr1"	,&out.digi_charge_integrated_corr1);
	SetBranchAddress("digi_max_amplitude_corr1"	,&out.digi_max_amplitude_corr1);

	SetBranchAddress("digi_charge_integrated_corr2"	,&out.digi_charge_integrated_corr2);
	SetBranchAddress("digi_max_amplitude_corr2"	,&out.digi_max_amplitude_corr2);
}

bool Filler::isActive(string name)
{
	map<string,int>::iterator it;
	it=activeBranches.find(name);
	if (it == activeBranches.end() ) return false;
	else return activeBranches[name];
}

void Filler::Fill( )
{ 
	//cout<<"[Filler]::[Fill] Fill tree:"<<fChain->GetEntries()<<endl;
	fChain->Fill() ;
}
