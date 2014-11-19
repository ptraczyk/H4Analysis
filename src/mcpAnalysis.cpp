#include "interface/mcpAnalysis.hpp"
#include <assert.h>

// map mcp numbers to digitser channels
unsigned int mcpmap[6]={0,4,7,6,5,8};

void mcpAnalysis::AnalyzeEvent()
{

  if (mapdigichannels.size()==0) {
    for (unsigned int iS=0; iS < l->nDigiSamples; iS++){
      unsigned int ch = l->digiChannel[iS];
      unsigned int gr = l->digiGroup[iS];
      unsigned int index = 8*gr+ch;
      if (mapdigichannels.find(index)==mapdigichannels.end()){
	unsigned int my = mapdigichannels.size();
	mapdigichannels.insert(std::make_pair<unsigned int,unsigned int>(index,my));
	cout << "Adding digitizer group="<<gr<<", channel="<<ch<<" as index " << my << endl;
      }
    }
    waveform.clear();
    for (unsigned int i=0; i<mapdigichannels.size(); i++) waveform.push_back(new Waveform());
    cout << "Found " << mapdigichannels.size() << " digitizer channels" << endl;
  }

  unsigned int nDigiChannels = mapdigichannels.size();

  for (unsigned int i=0; i<nDigiChannels; i++) waveform.at(i)->clear();
  l->digi_pedestal->clear();
  l->digi_pedestal_rms->clear();
  l->digi_max_amplitude->clear();
  l->digi_charge_integrated->clear();
  l->digi_time_at_max->clear();
  l->digi_time_at_frac30->clear();
  l->digi_time_at_frac50->clear();
  l->digi_pedestal->resize(nDigiChannels,-999);
  l->digi_pedestal_rms->resize(nDigiChannels,-999);
  l->digi_max_amplitude->resize(nDigiChannels,-999);
  l->digi_charge_integrated->resize(nDigiChannels,-999);
  l->digi_time_at_max->resize(nDigiChannels,-999);
  l->digi_time_at_frac30->resize(nDigiChannels,-999);
  l->digi_time_at_frac50->resize(nDigiChannels,-999);

  cout << " DIGI samples: " << l->nDigiSamples << endl;

  for (unsigned int iS=0; iS < l->nDigiSamples; iS++){
//    cout << "index" << iS;
//    cout << " " << l->digiSampleIndex[iS];
//*timeSampleUnit(l->digiFrequency[iS]);
//    cout << " " << l->digiSampleValue[iS] << endl;
    unsigned int index = mapdigichannels[l->digiGroup[iS]*8+l->digiChannel[iS]];
    //    cout << "debug " << l->digiGroup[iS] << " " << l->digiChannel[iS] << " " << index << endl;
    waveform.at(index)->addTimeAndSample(l->digiSampleIndex[iS]*timeSampleUnit(l->digiFrequency[iS]),l->digiSampleValue[iS]);
    for (int m=1;m<6;m++) {
      if (index==mcpmap[m]) l->FillHisto(Form("th1d_pulse_mcp%d",m),
				l->digiSampleIndex[iS],l->digiSampleValue[iS]);

    }    
  }
  
  for (unsigned int i=0; i<nDigiChannels; i++) {
//    cout << i << " " << waveform.at(i)->_samples.size() << endl;
    Waveform::baseline_informations wave_pedestal = waveform.at(i)->baseline(5,44);
    waveform.at(i)->offset(wave_pedestal.pedestal);
    waveform.at(i)->rescale(-1);
    Waveform::max_amplitude_informations wave_max = waveform.at(i)->max_amplitude(50,300,5);
    l->digi_pedestal->at(i)=wave_pedestal.pedestal;
    l->digi_pedestal_rms->at(i)=wave_pedestal.rms;
    l->digi_max_amplitude->at(i)=wave_max.max_amplitude;
    l->digi_charge_integrated->at(i)=waveform.at(i)->charge_integrated(0,900);
    l->digi_time_at_max->at(i)=wave_max.time_at_max*1.e9;
    l->digi_time_at_frac30->at(i)=waveform.at(i)->time_at_frac(wave_max.time_at_max-3.e-9,wave_max.time_at_max,0.3,wave_max,7)*1.e9;
    l->digi_time_at_frac50->at(i)=waveform.at(i)->time_at_frac(wave_max.time_at_max-3.e-9,wave_max.time_at_max,0.5,wave_max,7)*1.e9;
    //    cout << "pedestal " << i << " " << wave_pedestal.pedestal << " " << l->digi_pedestal->at(i) << endl; 
  }

  return;
}

void mcpAnalysis::Init(LoopAndFill *l1)
{
  cout<<"[mcpAnalysis]::[Init]"<<endl;
  BaseAnalysis::Init(l1);

    for( unsigned int iCh=1;iCh<6;++iCh) {
		cout<<"[mcpAnalysis]::[Init] Histo MCP"<<iCh<<"/" << 17 <<endl;
		// --- BOOKING THE HISTO THEMSELVEL TO HAVE BETTER RESULTS
		l->BookHisto(Form("th1d_pulse_mcp%d",iCh)," Pulse shape",1024,0.,1024.,"TH1D");
    }
  cout<<"[mcpAnalysis]::[Init]  Done"<<endl;
  return ;
}


float mcpAnalysis::timeSampleUnit(int drs4Freq)
{
  if (drs4Freq == 0)
    return 0.2E-9;
  else if (drs4Freq == 1)
    return 0.4E-9;
  else if (drs4Freq == 2)
    return 1.E-9;
  return -999.;
}
