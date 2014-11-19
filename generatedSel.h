/////////////////////////////////////////////////////////////////////////
//   This class has been automatically generated 
//   (at Tue Nov 18 18:28:47 2014 by ROOT version 5.34/20)
//   from TTree outputTree/outputTree
//   found on file: output.root
/////////////////////////////////////////////////////////////////////////


#ifndef generatedSel_h
#define generatedSel_h

// System Headers needed by the proxy
#if defined(__CINT__) && !defined(__MAKECINT__)
   #define ROOT_Rtypes
   #define ROOT_TError
#endif
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TPad.h>
#include <TH1.h>
#include <TSelector.h>
#include <TBranchProxy.h>
#include <TBranchProxyDirector.h>
#include <TBranchProxyTemplate.h>
#include <TFriendProxy.h>
using namespace ROOT;

// forward declarations needed by this particular proxy


// Header needed by this particular proxy
#include <vector>


class output_Interface {
   // This class defines the list of methods that are directly used by generatedSel,
   // and that can be overloaded in the user's script
public:
   void output_Begin(TTree*) {}
   void output_SlaveBegin(TTree*) {}
   Bool_t output_Notify() { return kTRUE; }
   Bool_t output_Process(Long64_t) { return kTRUE; }
   void output_SlaveTerminate() {}
   void output_Terminate() {}
};


class generatedSel : public TSelector, public output_Interface {
public :
   TTree          *fChain;         //!pointer to the analyzed TTree or TChain
   TH1            *htemp;          //!pointer to the histogram
   TBranchProxyDirector fDirector; //!Manages the proxys

   // Optional User methods
   TClass         *fClass;    // Pointer to this class's description

   // Proxy for each of the branches, leaves and friends of the tree
   TUIntProxy                        runNumber;
   TUIntProxy                        spillNumber;
   TUIntProxy                        evtNumber;
   TStlSimpleProxy<vector<float> >   BGOvalues;
   TStlSimpleProxy<vector<float> >   SCINTvalues;
   TStlSimpleProxy<vector<float> >   TDCreco;
   TStlSimpleProxy<vector<float> >   digi_charge_integrated;
   TStlSimpleProxy<vector<float> >   digi_max_amplitude;
   TStlSimpleProxy<vector<float> >   digi_SeePulse_Index;
   TStlSimpleProxy<vector<float> >   digi_SeePulse_Value;
   TStlSimpleProxy<vector<float> >   digi_Mib2Pulse_Index;
   TStlSimpleProxy<vector<float> >   digi_Mib2Pulse_Value;
   TStlSimpleProxy<vector<float> >   digi_Mib3Pulse_Index;
   TStlSimpleProxy<vector<float> >   digi_Mib3Pulse_Value;
   TStlSimpleProxy<vector<float> >   digi_Zstak1Pulse_Index;
   TStlSimpleProxy<vector<float> >   digi_Zstak1Pulse_Value;
   TStlSimpleProxy<vector<float> >   digi_Zstak2Pulse_Index;
   TStlSimpleProxy<vector<float> >   digi_Zstak2Pulse_Value;
   TStlSimpleProxy<vector<float> >   digi_pedestal;
   TStlSimpleProxy<vector<float> >   digi_pedestal_rms;
   TStlSimpleProxy<vector<float> >   digi_time_at_frac30;
   TStlSimpleProxy<vector<float> >   digi_time_at_frac50;
   TStlSimpleProxy<vector<float> >   digi_time_at_max;
   TStlSimpleProxy<vector<bool> >    HODOX1;
   TStlSimpleProxy<vector<bool> >    HODOX2;
   TStlSimpleProxy<vector<bool> >    HODOY1;
   TStlSimpleProxy<vector<bool> >    HODOY2;
   TFloatProxy                       TableX;
   TFloatProxy                       TableY;
   TFloatProxy                       CeF3HV;
   TFloatProxy                       BGOHV;
   TFloatProxy                       BeamEnergy;
   TFloatProxy                       BeamTilt;
   TIntProxy                         IsPhysics;
   TStlSimpleProxy<vector<float> >   digi_charge_integrated_sub;
   TStlSimpleProxy<vector<float> >   digi_max_amplitude_sub;
   TStlSimpleProxy<vector<float> >   digi_pedestal_sub;
   TStlSimpleProxy<vector<float> >   digi_pedestal_rms_sub;
   TStlSimpleProxy<vector<float> >   digi_charge_integrated_corr1;
   TStlSimpleProxy<vector<float> >   digi_max_amplitude_corr1;


   generatedSel(TTree *tree=0) : 
      fChain(0),
      htemp(0),
      fDirector(tree,-1),
      fClass                (TClass::GetClass("generatedSel")),
      runNumber                        (&fDirector,"runNumber"),
      spillNumber                      (&fDirector,"spillNumber"),
      evtNumber                        (&fDirector,"evtNumber"),
      BGOvalues                        (&fDirector,"BGOvalues"),
      SCINTvalues                      (&fDirector,"SCINTvalues"),
      TDCreco                          (&fDirector,"TDCreco"),
      digi_charge_integrated           (&fDirector,"digi_charge_integrated"),
      digi_max_amplitude               (&fDirector,"digi_max_amplitude"),
      digi_SeePulse_Index              (&fDirector,"digi_SeePulse_Index"),
      digi_SeePulse_Value              (&fDirector,"digi_SeePulse_Value"),
      digi_Mib2Pulse_Index             (&fDirector,"digi_Mib2Pulse_Index"),
      digi_Mib2Pulse_Value             (&fDirector,"digi_Mib2Pulse_Value"),
      digi_Mib3Pulse_Index             (&fDirector,"digi_Mib3Pulse_Index"),
      digi_Mib3Pulse_Value             (&fDirector,"digi_Mib3Pulse_Value"),
      digi_Zstak1Pulse_Index           (&fDirector,"digi_Zstak1Pulse_Index"),
      digi_Zstak1Pulse_Value           (&fDirector,"digi_Zstak1Pulse_Value"),
      digi_Zstak2Pulse_Index           (&fDirector,"digi_Zstak2Pulse_Index"),
      digi_Zstak2Pulse_Value           (&fDirector,"digi_Zstak2Pulse_Value"),
      digi_pedestal                    (&fDirector,"digi_pedestal"),
      digi_pedestal_rms                (&fDirector,"digi_pedestal_rms"),
      digi_time_at_frac30              (&fDirector,"digi_time_at_frac30"),
      digi_time_at_frac50              (&fDirector,"digi_time_at_frac50"),
      digi_time_at_max                 (&fDirector,"digi_time_at_max"),
      HODOX1                           (&fDirector,"HODOX1"),
      HODOX2                           (&fDirector,"HODOX2"),
      HODOY1                           (&fDirector,"HODOY1"),
      HODOY2                           (&fDirector,"HODOY2"),
      TableX                           (&fDirector,"TableX"),
      TableY                           (&fDirector,"TableY"),
      CeF3HV                           (&fDirector,"CeF3HV"),
      BGOHV                            (&fDirector,"BGOHV"),
      BeamEnergy                       (&fDirector,"BeamEnergy"),
      BeamTilt                         (&fDirector,"BeamTilt"),
      IsPhysics                        (&fDirector,"IsPhysics"),
      digi_charge_integrated_sub       (&fDirector,"digi_charge_integrated_sub"),
      digi_max_amplitude_sub           (&fDirector,"digi_max_amplitude_sub"),
      digi_pedestal_sub                (&fDirector,"digi_pedestal_sub"),
      digi_pedestal_rms_sub            (&fDirector,"digi_pedestal_rms_sub"),
      digi_charge_integrated_corr1     (&fDirector,"digi_charge_integrated_corr1"),
      digi_max_amplitude_corr1         (&fDirector,"digi_max_amplitude_corr1")
      { }
   ~generatedSel();
   Int_t   Version() const {return 1;}
   void    Begin(::TTree *tree);
   void    SlaveBegin(::TTree *tree);
   void    Init(::TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SlaveTerminate();
   void    Terminate();

   ClassDef(generatedSel,0);


//inject the user's code
#include "output.root"
};

#endif


#ifdef __MAKECINT__
#pragma link C++ class generatedSel;
#endif


inline generatedSel::~generatedSel() {
   // destructor. Clean up helpers.

}

inline void generatedSel::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fDirector.SetTree(fChain);
   if (htemp == 0) {
      htemp = fDirector.CreateHistogram(GetOption());
      htemp->SetTitle("output.root");
      fObject = htemp;
   }
}

Bool_t generatedSel::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   fDirector.SetTree(fChain);
   output_Notify();
   
   return kTRUE;
}
   

inline void generatedSel::Begin(TTree *tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   output_Begin(tree);

}

inline void generatedSel::SlaveBegin(TTree *tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   Init(tree);

   output_SlaveBegin(tree);

}

inline Bool_t generatedSel::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either TTree::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.

   // WARNING when a selector is used with a TChain, you must use
   //  the pointer to the current TTree to call GetEntry(entry).
   //  The entry is always the local entry number in the current tree.
   //  Assuming that fChain is the pointer to the TChain being processed,
   //  use fChain->GetTree()->GetEntry(entry).


   fDirector.SetReadEntry(entry);
   htemp->Fill(output());
   output_Process(entry);
   return kTRUE;

}

inline void generatedSel::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   output_SlaveTerminate();
}

inline void generatedSel::Terminate()
{
   // Function called at the end of the event loop.
   htemp = (TH1*)fObject;
   Int_t drawflag = (htemp && htemp->GetEntries()>0);
   
   if (gPad && !drawflag && !fOption.Contains("goff") && !fOption.Contains("same")) {
      gPad->Clear();
   } else {
      if (fOption.Contains("goff")) drawflag = false;
      if (drawflag) htemp->Draw(fOption);
   }
   output_Terminate();
}
