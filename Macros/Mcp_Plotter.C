#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

#include "TFile.h"
#include "TLatex.h"
#include "TLine.h"
#include "TColor.h"
#include "TTree.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TProfile.h"
#include "TChain.h"
#include "TMath.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include "TFitter.h"
#include "tdrStyle.C"

#define LIGHT 299.792458
#define NSTEPMAX 10000
//#define DEBUG

double deltaPhi(double phi1, double phi2);
double deltaR(double eta1, double eta2, double phi1, double phi2);
double DR_xyz(double x, double y, double z);
TH1F** InitTimeLayerHistograms(const char *name, const char *title, int size, int Bin, float Min, float max, string Title, string Mode );
void deleteTimeLayerPlot(TH1F **h, int size);

//root -q .x Mcp_Plotter.C+
void Mcp_Plotter( TString InputFile = "../output.root", TString OutPutFolder = "my_plots" ){
  //Initial Messages
  cout<<"Let's start to do some cool plots!"<<endl;
  //Parameters---------------------------------------------------
  bool debug=false;
  int Nplots_single = 8.;
  //Parameters---------------------------------------------------
#ifdef DEBUG
  debug=true;
#endif
  //SuperPaletta
  setTDRStyle();
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  TCanvas* myc1 = new TCanvas("myc1", "CMS", 1000, 1000);
  using namespace std;
  //OutputFolder
  TString Comm = "mkdir -p " + OutPutFolder;
  system( Comm.Data() );
  Comm = "mkdir -p " + OutPutFolder + "/SingleEvents";
  system( Comm.Data() );
  TFile* File = TFile::Open( InputFile.Data() );
  TTree* Tree = (TTree*) File->Get("outputTree");
  myc1->cd();
  gStyle->SetPalette(1);
  //TTree
  Long64_t nentries = Tree->GetEntriesFast();
  cout<<"Creating array (wait for confirmation)"<<endl;
  std::vector<float> *digi_SeePulse_Index = new vector<float>, *digi_SeePulse_Value = new vector<float>;
  cout<<"Array created."<<endl;
  //TTree
  Tree->SetBranchAddress( "digi_SeePulse_Index", &digi_SeePulse_Index);
  Tree->SetBranchAddress( "digi_SeePulse_Value", &digi_SeePulse_Value);

  //Single events plots
  TH1F *h_Shape;
  //Plots Single events but on All events
  TH1F *nEv             = new TH1F("nEv","N events, Selec", 3, -0.5, 1.5); nEv->GetXaxis()->SetTitle("#Ev");
  myc1->cd();

  //LOOP-------
  cout<<"Starting the Loop! Running on: "<<nentries<<" events."<<endl;
  for(Long64_t iEntry=0; iEntry < nentries; iEntry++){
    //Initialization
    if( iEntry%1000==0 ) cout<<"You are at the "<<iEntry<<"/"<<nentries<<" event"<<endl;
    stringstream ss;
    ss << iEntry;
    Tree->GetEntry(iEntry);
    if( iEntry < Nplots_single ){
	h_Shape            = new TH1F("h_Shape","Pulse Shape", 1024, -0.5, 1023.5); h_Shape->GetXaxis()->SetTitle("Index"); h_Shape->GetYaxis()->SetTitle("Value");
    }
    //Real Plots
    nEv->SetBinContent(1,nEv->GetBinContent(1)+1);
    if( iEntry < Nplots_single ){
	for(int i=0; i<1024; i++){
	  //cout<<"AAA: "<<digi_SeePulse_Index[i]<<" and "<<digi_SeePulse_Value[i]<<endl;
	  h_Shape->SetBinContent( digi_SeePulse_Index->at(i), digi_SeePulse_Value->at(i) );
	  //cout<<"AAA: "<<digi_SeePulse_Index->size()<<endl;
	  //cout<<"AAA: "<<digi_SeePulse_Index->at(2)<<" and "<<digi_SeePulse_Value->at(2)<<endl;
	  //h_Shape->SetBinContent( *(digi_SeePulse_Index->at(i+1)), *(digi_SeePulse_Value->at(i+1)) );
	}
    }
    //Drawning Single Event Histos
    if( iEntry < Nplots_single ){
	h_Shape->Draw(); TString out = OutPutFolder + "/SingleEvents/PulseShape_"+ ss.str() +".png"; myc1->SaveAs( out.Data() ); delete h_Shape;
    }
  }//All Entries
  //Plots
  myc1->cd();
  nEv->Draw(); gStyle->SetOptStat(0); TString  out1 = OutPutFolder + "/All_Nevent.png"; myc1->SaveAs( out1.Data() ); delete nEv;
  delete myc1;
}

double deltaPhi(double phi1, double phi2) { 
  double result = phi1 - phi2;
  while (result > M_PI) result -= 2*M_PI;
  while (result <= -M_PI) result += 2*M_PI;
  return result;
}
double deltaR(double eta1, double eta2, double phi1, double phi2) {
  return sqrt( pow(eta2-eta1,2 ) +  pow( deltaPhi(phi1, phi2),2 )  );
}

double DR_xyz(double x, double y, double z){
  return sqrt( pow(x,2 ) + pow(y,2 ) + pow(z,2 ) );
}

TH1F** InitTimeLayerHistograms(const char *name, const char *title, int size, int Bin, float Min, float Max, string Title, string Mode ){
  TH1F **h = new TH1F*[size];
  char name_c[100];
  char title_c[200];
  for(int jR=0; jR<size; jR++){
    if( Mode=="etaphi" )   {
	sprintf(title_c, "%s < %.3f", title, jR*0.003+0.003);
	sprintf(name_c, "%s%d", name, jR);
    }
    else if( Mode=="xtal" ){
	sprintf(name_c, "%s%d", name, jR);
	if(jR==0) sprintf(title_c, "%s Seed", title);
	if(jR==1) sprintf(title_c, "%s +1 iPhi, -1 iEta", title);
	if(jR==2) sprintf(title_c, "%s +1 iPhi,  0 iEta", title);
	if(jR==3) sprintf(title_c, "%s +1 iPhi, +1 iEta", title);
	if(jR==4) sprintf(title_c, "%s  0 iPhi, -1 iEta", title);
	if(jR==5) sprintf(title_c, "%s  0 iPhi, +1 iEta", title);
	if(jR==6) sprintf(title_c, "%s -1 iPhi, -1 iEta", title);
	if(jR==7) sprintf(title_c, "%s -1 iPhi,  0 iEta", title);
	if(jR==8) sprintf(title_c, "%s -1 iPhi, +1 iEta", title);
    }
    else                   {
	sprintf(title_c, "%s %d", title, jR);
	sprintf(name_c, "%s%d", name, jR);
    }
    h[jR] = new TH1F(name_c, title_c, Bin, Min, Max);
    h[jR]->GetXaxis()->SetTitle(Title.c_str());
    h[jR]->Sumw2();
  }
  return h;
}

void deleteTimeLayerPlot(TH1F **h, int size){
  for(int jR=0; jR<size; jR++)
    delete h[jR];
  delete h;
}
