#include "interface/McpRecoAnalysis.hpp"
#include <assert.h>


void McpRecoAnalysis::AnalyzeEvent()
{
  v_Digiindex_SEE.clear(); v_DigiValue_SEE.clear();
  v_Digiindex_MIB2.clear(); v_DigiValue_MIB2.clear();
  v_Digiindex_MIB3.clear(); v_DigiValue_MIB3.clear();
  v_Digiindex_Zstak1.clear(); v_DigiValue_Zstak1.clear();
  v_Digiindex_Zstak2.clear(); v_DigiValue_Zstak2.clear();
  for (unsigned int iSample=0;iSample< l->nDigiSamples;iSample++)
  {
    //fill waveform
    UInt_t digiGroup   = l->digiGroup[iSample];
    UInt_t digiChannel_tot = l->digiChannel[iSample] + 8*digiGroup; // update this in order to consider also the group. for us the group is always 0
    UInt_t digiChannel = l->digiChannel[iSample];
    UInt_t digiSampleIndex = l->digiSampleIndex[iSample];
    Float_t digiSampleValue = l->digiSampleValue[iSample];
    if (inputType==1) digiSampleValue=l->digiSampleValueSub[iSample];
    if (int(digiChannel_tot) >= nChannels) continue;
    //Save SEE
    if( int(digiGroup)==SEE_gr && int(digiChannel)==SEE_ch ){
	v_Digiindex_SEE.push_back( float(digiSampleIndex) );
	v_DigiValue_SEE.push_back( float(digiSampleValue) );
    }
    else if( int(digiGroup)==MIB2_gr && int(digiChannel)==MIB2_ch ){
	v_Digiindex_MIB2.push_back( float(digiSampleIndex) );
	v_DigiValue_MIB2.push_back( float(digiSampleValue) );
    }
    else if( int(digiGroup)==MIB3_gr && int(digiChannel)==MIB3_ch ){
	v_Digiindex_MIB3.push_back( float(digiSampleIndex) );
	v_DigiValue_MIB3.push_back( float(digiSampleValue) );
    }
    else if( int(digiGroup)==Zstak1_gr && int(digiChannel)==Zstak1_ch ){
	v_Digiindex_Zstak1.push_back( float(digiSampleIndex) );
	v_DigiValue_Zstak1.push_back( float(digiSampleValue) );
    }
    else if( int(digiGroup)==Zstak2_gr && int(digiChannel)==Zstak2_ch ){
	v_Digiindex_Zstak2.push_back( float(digiSampleIndex) );
	v_DigiValue_Zstak2.push_back( float(digiSampleValue) );
    }
  }

  l->digi_SeePulse_Index->clear();
  l->digi_SeePulse_Value->clear();
  l->digi_Mib2Pulse_Index->clear();
  l->digi_Mib2Pulse_Value->clear();
  l->digi_Mib3Pulse_Index->clear();
  l->digi_Mib3Pulse_Value->clear();
  l->digi_Zstak1Pulse_Index->clear();
  l->digi_Zstak1Pulse_Value->clear();
  l->digi_Zstak2Pulse_Index->clear();
  l->digi_Zstak2Pulse_Value->clear();
  l->digi_SeePulse_Index->resize(v_Digiindex_SEE.size(),-999);
  l->digi_SeePulse_Value->resize(v_Digiindex_SEE.size(),-999);
  l->digi_Mib2Pulse_Index->resize(v_Digiindex_MIB2.size(),-999);
  l->digi_Mib2Pulse_Value->resize(v_Digiindex_MIB2.size(),-999);
  l->digi_Mib3Pulse_Index->resize(v_Digiindex_MIB3.size(),-999);
  l->digi_Mib3Pulse_Value->resize(v_Digiindex_MIB3.size(),-999);
  l->digi_Zstak1Pulse_Index->resize(v_Digiindex_Zstak1.size(),-999);
  l->digi_Zstak1Pulse_Value->resize(v_Digiindex_Zstak1.size(),-999);
  l->digi_Zstak2Pulse_Index->resize(v_Digiindex_Zstak2.size(),-999);
  l->digi_Zstak2Pulse_Value->resize(v_Digiindex_Zstak2.size(),-999);
  for(unsigned int i=0; i<v_Digiindex_SEE.size(); i++){
    if (l->digi_SeePulse_Index != NULL) l->digi_SeePulse_Index->at(i) = v_Digiindex_SEE[i];
    if (l->digi_SeePulse_Value != NULL) l->digi_SeePulse_Value->at(i) = v_DigiValue_SEE[i];
  }
  for(unsigned int i=0; i<v_Digiindex_MIB2.size(); i++){
    if (l->digi_Mib2Pulse_Index != NULL) l->digi_Mib2Pulse_Index->at(i) = v_Digiindex_MIB2[i];
    if (l->digi_Mib2Pulse_Value != NULL) l->digi_Mib2Pulse_Value->at(i) = v_DigiValue_MIB2[i];
  }
  for(unsigned int i=0; i<v_Digiindex_MIB3.size(); i++){
    if (l->digi_Mib3Pulse_Index != NULL) l->digi_Mib3Pulse_Index->at(i) = v_Digiindex_MIB3[i];
    if (l->digi_Mib3Pulse_Value != NULL) l->digi_Mib3Pulse_Value->at(i) = v_DigiValue_MIB3[i];
  }
  for(unsigned int i=0; i<v_Digiindex_Zstak1.size(); i++){
    if (l->digi_Zstak1Pulse_Index != NULL) l->digi_Zstak1Pulse_Index->at(i) = v_Digiindex_Zstak1[i];
    if (l->digi_Zstak1Pulse_Value != NULL) l->digi_Zstak1Pulse_Value->at(i) = v_DigiValue_Zstak1[i];
  }
  for(unsigned int i=0; i<v_Digiindex_Zstak2.size(); i++){
    if (l->digi_Zstak2Pulse_Index != NULL) l->digi_Zstak2Pulse_Index->at(i) = v_Digiindex_Zstak2[i];
    if (l->digi_Zstak2Pulse_Value != NULL) l->digi_Zstak2Pulse_Value->at(i) = v_DigiValue_Zstak2[i];
  }
  return;
}

void McpRecoAnalysis::Init(LoopAndFill *l1)
{
  cout<<"[McpRecoAnalysis]::[Init]"<<endl;
  BaseAnalysis::Init(l1);

  cout<<"[McpRecoAnalysis]::[Init]::Done"<<endl;
  return ;
}



void McpRecoAnalysis::FillTdc(){

  l->TDCreco->clear();
  l->TDCreco->resize(2,-999);

  std::vector<unsigned int> tdc_readings[4];

  float tdc_recox=-999;
  float tdc_recoy=-999;
  for (unsigned int i=0; i<l->nTdcChannels; i++){
    if (l->tdcBoard[i]==0x07030001 && l->tdcChannel[i]<4){
	tdc_readings[l->tdcChannel[i]].push_back((float)l->tdcData[i]);
    }
  }
  if (tdc_readings[wcXl].size()!=0 && tdc_readings[wcXr].size()!=0){
    float TXl = *std::min_element(tdc_readings[wcXl].begin(),tdc_readings[wcXl].begin()+tdc_readings[wcXl].size());
    float TXr = *std::min_element(tdc_readings[wcXr].begin(),tdc_readings[wcXr].begin()+tdc_readings[wcXr].size());
    float X = (TXr-TXl)*0.005; // = /40./5./10. //position in cm 0.2mm/ns with 25ps LSB TDC
    tdc_recox = X;
  }
  if (tdc_readings[wcYd].size()!=0 && tdc_readings[wcYu].size()!=0){
    float TYd = *std::min_element(tdc_readings[wcYd].begin(),tdc_readings[wcYd].begin()+tdc_readings[wcYd].size());
    float TYu = *std::min_element(tdc_readings[wcYu].begin(),tdc_readings[wcYu].begin()+tdc_readings[wcYu].size());
    float Y = (TYu-TYd)*0.005; // = /40./5./10. //position in cm 0.2mm/ns with 25ps LSB TDC
    tdc_recoy = Y;
  }

  if (tdc_recox>-999 && tdc_recoy>-999){
    l->TDCreco->at(0)=tdc_recox;
    l->TDCreco->at(1)=tdc_recoy;
  }

}


void McpRecoAnalysis::FillHodo(){

  l->HODOX1->clear();  l->HODOX1->resize(nFibersHodo,false);
  l->HODOX2->clear();  l->HODOX2->resize(nFibersHodo,false);
  l->HODOY1->clear();  l->HODOY1->resize(nFibersHodo,false);
  l->HODOY2->clear();  l->HODOY2->resize(nFibersHodo,false);

  std::vector<bool> *hodo;

  for(unsigned int i=0;i<l->nPatterns;++i){
    if(l->patternBoard[i]==0x08030001 || l->patternBoard[i]==0x08030002){
	// here is where the hodoscope mapping is done
	if (l->patternBoard[i]==0x08030001){
	  if (l->patternChannel[i]<2) hodo=l->HODOY2;
	  else hodo=l->HODOX2;
	}
	else if (l->patternBoard[i]==0x08030002){
	  if (l->patternChannel[i]<2) hodo=l->HODOY1;
	  else hodo=l->HODOX1;
	}
	std::vector<int> *fiberorder =(bool)( l->patternChannel[i]&0b1) ? &fiberOrderB : &fiberOrderA;
	for (unsigned int j=0; j<32; j++){
	  bool thisfibon = (l->pattern[i]>>j)&0b1;
	  hodo->at(fiberorder->at(j)-1)=thisfibon;
	}

    }
  }

}


void McpRecoAnalysis::FillFiberOrder(){

  fiberOrderA.clear();
  fiberOrderB.clear();

  fiberOrderA.push_back(31);
  fiberOrderA.push_back(29);
  fiberOrderA.push_back(23);
  fiberOrderA.push_back(21);
  fiberOrderA.push_back(5);
  fiberOrderA.push_back(7);
  fiberOrderA.push_back(15);
  fiberOrderA.push_back(13);
  fiberOrderA.push_back(1);
  fiberOrderA.push_back(3);
  fiberOrderA.push_back(11);
  fiberOrderA.push_back(9);
  fiberOrderA.push_back(6);
  fiberOrderA.push_back(8);
  fiberOrderA.push_back(16);
  fiberOrderA.push_back(14);
  fiberOrderA.push_back(17);
  fiberOrderA.push_back(27);
  fiberOrderA.push_back(19);
  fiberOrderA.push_back(25);
  fiberOrderA.push_back(24);
  fiberOrderA.push_back(22);
  fiberOrderA.push_back(32);
  fiberOrderA.push_back(30);
  fiberOrderA.push_back(4);
  fiberOrderA.push_back(2);
  fiberOrderA.push_back(12);
  fiberOrderA.push_back(10);
  fiberOrderA.push_back(20);
  fiberOrderA.push_back(18);
  fiberOrderA.push_back(28);
  fiberOrderA.push_back(26);

  fiberOrderB.push_back(54);
  fiberOrderB.push_back(64);
  fiberOrderB.push_back(56);
  fiberOrderB.push_back(62);
  fiberOrderB.push_back(49);
  fiberOrderB.push_back(51);
  fiberOrderB.push_back(59);
  fiberOrderB.push_back(57);
  fiberOrderB.push_back(53);
  fiberOrderB.push_back(55);
  fiberOrderB.push_back(63);
  fiberOrderB.push_back(61);
  fiberOrderB.push_back(45);
  fiberOrderB.push_back(47);
  fiberOrderB.push_back(37);
  fiberOrderB.push_back(39);
  fiberOrderB.push_back(34);
  fiberOrderB.push_back(42);
  fiberOrderB.push_back(36);
  fiberOrderB.push_back(44);
  fiberOrderB.push_back(50);
  fiberOrderB.push_back(52);
  fiberOrderB.push_back(58);
  fiberOrderB.push_back(60);
  fiberOrderB.push_back(38);
  fiberOrderB.push_back(48);
  fiberOrderB.push_back(40);
  fiberOrderB.push_back(46);
  fiberOrderB.push_back(41);
  fiberOrderB.push_back(43);
  fiberOrderB.push_back(33);
  fiberOrderB.push_back(35);

}

float McpRecoAnalysis::timeSampleUnit(int drs4Freq)
{
  if (drs4Freq == 0)
    return 0.2E-9;
  else if (drs4Freq == 1)
    return 0.4E-9;
  else if (drs4Freq == 2)
    return 1.E-9;
  return -999.;
}
