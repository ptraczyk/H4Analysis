#include "interface/PlotAnalysis.hpp"

void PlotAnalysis::Init(LoopAndFill *l1)
{
	cout<<"[PlotAnalysis]::[Init]"<<endl;
	BaseAnalysis::Init(l1);
	for(unsigned int i=0;i<E.size() ;++i)
	   for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
		{
		cout<<"[PlotAnalysis]::[Init] Histo ch="<<iCh<<"/"<<nChannels<<" E="<<E[i]<<endl;
		l->BookHisto(Form("tprofile_chint_sub_ch%d_E%d",iCh,E[i]),"ch_int_sub vs HV",2000,-0.5,1999.5,"TProfile");
		l->BookHisto(Form("tprofile_maxampl_sub_ch%d_E%d",iCh,E[i]),"ch_int_sub vs HV",2000,-0.5,1999.5,"TProfile");
		}
	cout<<"[PlotAnalysis]::[Init] Done"<<endl;
}

bool PlotAnalysis::isActiveRun(int run){
	//cache
	static int lastRun=-1;
	static bool lastValue;
	if (run == lastRun) return lastValue;

	auto it=runs.find(run);
	if (it==runs.end() ){ lastValue=false;return false;}
	if (it->second) {lastValue=true ;return true;}
	else {lastValue=false;return false;}
}

void PlotAnalysis::AnalyzeEvent(){
	if (!runs.empty()  && !isActiveRun(l->runNumber)){return;}
	// table selection
	if (int(l->TableX) !=194 || int(l->TableY) !=254 ) {return;} //center table position

	for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
		{
		if ( (*l->digi_charge_integrated_sub)[iCh]>10)
			l->FillProfile(Form("tprofile_chint_sub_ch%d_E%d",iCh,int(l->BeamEnergy)),
				l->CeF3HV,//x
				(*l->digi_charge_integrated_sub)[iCh]//y
				);
		if ( (*l->digi_max_amplitude_sub)[iCh]>10)
			l->FillProfile(Form("tprofile_maxampl_sub_ch%d_E%d",iCh,int(l->BeamEnergy)),
				l->CeF3HV,//x
				(*l->digi_max_amplitude_sub)[iCh]//y
				);
		}
}
