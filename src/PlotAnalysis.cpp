#include "interface/PlotAnalysis.hpp"

void PlotAnalysis::Init(LoopAndFill *l1)
{
	cout<<"[PlotAnalysis]::[Init]"<<endl;
	BaseAnalysis::Init(l1);
	for(unsigned int i=0;i<E.size() ;++i)
	   for( unsigned int iCh=0;iCh<nChannels;++iCh)
		{
		cout<<"[PlotAnalysis]::[Init] Histo ch="<<iCh<<"/"<<nChannels<<"E="<<E[i]<<endl;
		l->BookHisto(Form("tprofile_chint_sub_ch%d_E%d",iCh,E[i]),"ch_int_sub vs HV",2000,-0.5,1999.5,"TProfile");
		l->BookHisto(Form("tprofile_maxampl_sub_ch%d_E%d",iCh,E[i]),"ch_int_sub vs HV",2000,-0.5,1999.5,"TProfile");
		}
	cout<<"[PlotAnalysis]::[Init] Done"<<endl;
}


void PlotAnalysis::AnalyzeEvent(){
	for( unsigned int iCh=0;iCh<nChannels;++iCh)
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
