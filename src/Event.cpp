#include "interface/Event.hpp"


tree::tree(){
	ADCvalues =new              vector<float> ; 
	BGOvalues =new              vector<float> ; 
	SCINTvalues =new            vector<float> ; 
	TDCreco   =new              vector<float> ; 
	digi_charge_integrated =new vector<float> ; 
	digi_max_amplitude =new     vector<float> ; 
	digi_SeePulse_Index =new    vector<float> ; 
	digi_SeePulse_Value =new    vector<float> ; 
	digi_Mib2Pulse_Index =new   vector<float> ; 
	digi_Mib2Pulse_Value =new   vector<float> ; 
	digi_Mib3Pulse_Index =new   vector<float> ; 
	digi_Mib3Pulse_Value =new   vector<float> ; 
	digi_Zstak1Pulse_Index =new vector<float> ; 
	digi_Zstak1Pulse_Value =new vector<float> ; 
	digi_Zstak2Pulse_Index =new vector<float> ; 
	digi_Zstak2Pulse_Value =new vector<float> ; 
	digi_pedestal =new          vector<float> ; 
	digi_pedestal_rms =new      vector<float> ; 
	digi_time_at_frac30 =new    vector<float> ; 
	digi_time_at_frac50 =new    vector<float> ; 
	digi_time_at_max =new       vector<float> ; 
	HODOX1    =new              vector<bool>  ; 
	HODOX2    =new              vector<bool>  ; 
	HODOY1    =new              vector<bool>  ; 
	HODOY2    =new              vector<bool>  ; 

	digi_charge_integrated_sub =new vector<float> ; 
	digi_max_amplitude_sub =new     vector<float> ; 
	digi_pedestal_sub =new          vector<float> ; 
	digi_pedestal_rms_sub =new      vector<float> ; 

	digi_charge_integrated_corr1 =new vector<float> ; 
	digi_max_amplitude_corr1 =new     vector<float> ; 

	digi_charge_integrated_corr2 =new vector<float> ; 
	digi_max_amplitude_corr2 =new     vector<float> ; 
}

tree::~tree(){
	delete ADCvalues ;
	delete BGOvalues ;
	delete SCINTvalues ;
	delete TDCreco   ;
	delete digi_charge_integrated ;
	delete digi_max_amplitude ;
	delete digi_SeePulse_Index ;
	delete digi_SeePulse_Value ;
	delete digi_Mib2Pulse_Index ;
	delete digi_Mib2Pulse_Value ;
	delete digi_Mib3Pulse_Index ;
	delete digi_Mib3Pulse_Value ;
	delete digi_Zstak1Pulse_Index ;
	delete digi_Zstak1Pulse_Value ;
	delete digi_Zstak2Pulse_Index ;
	delete digi_Zstak2Pulse_Value ;
	delete digi_pedestal ;
	delete digi_pedestal_rms ;
	delete digi_time_at_frac30 ;
	delete digi_time_at_frac50 ;
	delete digi_time_at_max ;
	delete HODOX1    ;
	delete HODOX2    ;
	delete HODOY1    ;
	delete HODOY2    ;

	delete digi_charge_integrated_sub ;
	delete digi_max_amplitude_sub ;
	delete digi_pedestal_sub ;
	delete digi_pedestal_rms_sub ;

	delete digi_charge_integrated_corr1 ;
	delete digi_max_amplitude_corr1 ;

	delete digi_charge_integrated_corr2 ;
	delete digi_max_amplitude_corr2 ;
}
