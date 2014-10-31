#include "interface/LooperAndFiller.hpp"

void LoopAndFill::Init(){
	Looper::Init();
	Filler::Init();
}

void LoopAndFill::Close()
{
	Filler::Close();
}

void LoopAndFill::Fill(){
	// I cannot use virtual Inheritance because we have vectors
	// otherwise I would have done it ;-)
	//copy from this to out->
	//
	out.runNumber	=runNumber;
	out.spillNumber	=spillNumber;
	out.evtNumber	=evtNumber;
	// ---- H4tree ---
	out.evtTimeDist = evtTimeDist;
	out.evtTimeStart = evtTimeStart;
	out.nEvtTimes = nEvtTimes;
	CopyArray(evtTime,out.evtTime,nEvtTimes);
	CopyArray(evtTimeBoard,out.evtTimeBoard,nEvtTimes);

	out.nAdcChannels = nAdcChannels;
	out.nTdcChannels= nTdcChannels;
	out.nDigiSamples= nDigiSamples;
	out.nScalerWords= nScalerWords;
	out.nPatterns=    nPatterns;
	out.nTriggerWords=nTriggerWords;

	CopyArray(adcBoard,out.adcBoard,nAdcChannels);
	CopyArray(adcChannel,out.adcChannel,nAdcChannels);
	CopyArray(adcData,out.adcData,nAdcChannels);
	
	CopyArray(tdcBoard,out.tdcBoard,nTdcChannels);
	CopyArray(tdcChannel,out.tdcChannel,nTdcChannels);
	CopyArray(tdcData,out.tdcData,nTdcChannels);

	CopyArray(digiFrequency,out.digiFrequency,nDigiSamples);
	CopyArray(digiGroup,out.digiGroup,nDigiSamples);
	CopyArray(digiChannel,out.digiChannel,nDigiSamples);
	CopyArray(digiSampleIndex,out.digiSampleIndex,nDigiSamples);
	CopyArray(digiSample,out.digiSample,nDigiSamples);
	CopyArray(digiBoard,out.digiBoard,nDigiSamples);

	CopyArray(scalerWord,out.scalerWord,nScalerWords);
	CopyArray(scalerBoard,out.scalerBoard,nScalerWords);

	CopyArray(pattern,out.pattern,nPatterns);
	CopyArray(patternBoard,out.patternBoard,nPatterns);
	CopyArray(patternChannel,out.patternChannel,nPatterns);

	CopyArray(triggerWords,out.triggerWords,nTriggerWords);
	CopyArray(triggerWordsBoard,out.triggerWordsBoard,nTriggerWords);
	// ---- dqmTree ----
 	CopyVector(ADCvalues             ,out.ADCvalues);
 	CopyVector(BGOvalues             ,out.BGOvalues);
 	CopyVector(SCINTvalues           ,out.SCINTvalues);
 	CopyVector(TDCreco               ,out.TDCreco);
 	CopyVector(digi_charge_integrated,out.digi_charge_integrated);
 	CopyVector(digi_max_amplitude    ,out.digi_max_amplitude);
 	CopyVector(digi_pedestal         ,out.digi_pedestal);
 	CopyVector(digi_pedestal_rms     ,out.digi_pedestal_rms);
 	CopyVector(digi_time_at_frac30   ,out.digi_time_at_frac30);
 	CopyVector(digi_time_at_frac50   ,out.digi_time_at_frac50);
 	CopyVector(digi_time_at_max      ,out.digi_time_at_max);
 	CopyVector(HODOX1                ,out.HODOX1);
 	CopyVector(HODOX2                ,out.HODOX2);
 	CopyVector(HODOY1                ,out.HODOY1);
 	CopyVector(HODOY2                ,out.HODOY2);
			
}
