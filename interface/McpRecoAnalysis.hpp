#ifndef PEDESTAL_ANALYSIS_H
#define PEDESTAL_ANALYSIS_H

#include "interface/BaseAnalysis.hpp"
#include "interface/LooperAndFiller.hpp"
#include "interface/Waveform.hpp"
#include <algorithm>
#include <map>

#define wcXl 0
#define wcXr 1
#define wcYd 3
#define wcYu 2

#define nFibersHodo 64
#define nBGOChannels 24
#define nSCINTChannels 4

class McpRecoAnalysis : public BaseAnalysis
{
vector<float> v_Digiindex_SEE;
vector<float> v_DigiValue_SEE;
vector<float> v_Digiindex_MIB2;
vector<float> v_DigiValue_MIB2;
vector<float> v_Digiindex_MIB3;
vector<float> v_DigiValue_MIB3;
vector<float> v_Digiindex_Zstak1;
vector<float> v_DigiValue_Zstak1;
vector<float> v_Digiindex_Zstak2;
vector<float> v_DigiValue_Zstak2;
public:
	int nChannels;
	int minPed;
	int maxPed;
	int inputType; // 0 = base; 1=sub
	int SEE_gr;
	int SEE_ch;
	int MIB2_gr;
	int MIB2_ch;
	int MIB3_gr;
	int MIB3_ch;
	int Zstak1_gr;
	int Zstak1_ch;
	int Zstak2_gr;
	int Zstak2_ch;
	McpRecoAnalysis(){
	  minPed=5; maxPed=44; nChannels=32; inputType=0;
	  SEE_gr=0; SEE_ch=6;
	  MIB2_gr=0; MIB2_ch=4;
	  MIB3_gr=1; MIB3_ch=0;
	  Zstak1_gr=0; Zstak1_ch=5;
	  Zstak2_gr=0; Zstak2_ch=7;
	  v_Digiindex_SEE.clear(); v_DigiValue_SEE.clear(); 
	  v_Digiindex_MIB2.clear(); v_DigiValue_MIB2.clear(); 
	  v_Digiindex_MIB3.clear(); v_DigiValue_MIB3.clear(); 
	  v_Digiindex_Zstak1.clear(); v_DigiValue_Zstak1.clear(); 
	  v_Digiindex_Zstak2.clear(); v_DigiValue_Zstak2.clear(); 
	};
	~McpRecoAnalysis(){};
	void Init(LoopAndFill *l1); // { l = l1 ; };
	void AnalyzeEvent();
  void FillTdc();
  std::vector<int> fiberOrderA;
  std::vector<int> fiberOrderB;
  void FillHodo();
  void FillFiberOrder();

  std::map<unsigned int,unsigned int> mapdigichannels;
  std::vector<Waveform*> waveforms;
  float timeSampleUnit(int drs4Freq);

};

#endif

