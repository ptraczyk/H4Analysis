#include "interface/Event.hpp"


tree::tree(){
	ADCvalues =new              vector<float> ; 
	BGOvalues =new              vector<float> ; 
	SCINTvalues =new            vector<float> ; 
	TDCreco   =new              vector<float> ; 
	digi_charge_integrated =new vector<float> ; 
	digi_max_amplitude =new     vector<float> ; 
	digi_pedestal =new          vector<float> ; 
	digi_pedestal_rms =new      vector<float> ; 
	digi_time_at_frac30 =new    vector<float> ; 
	digi_time_at_frac50 =new    vector<float> ; 
	digi_time_at_max =new       vector<float> ; 
	HODOX1    =new              vector<bool>  ; 
	HODOX2    =new              vector<bool>  ; 
	HODOY1    =new              vector<bool>  ; 
	HODOY2    =new              vector<bool>  ; 

}

tree::~tree(){
	delete ADCvalues ;
	delete BGOvalues ;
	delete SCINTvalues ;
	delete TDCreco   ;
	delete digi_charge_integrated ;
	delete digi_max_amplitude ;
	delete digi_pedestal ;
	delete digi_pedestal_rms ;
	delete digi_time_at_frac30 ;
	delete digi_time_at_frac50 ;
	delete digi_time_at_max ;
	delete HODOX1    ;
	delete HODOX2    ;
	delete HODOY1    ;
	delete HODOY2    ;
}
