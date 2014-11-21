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
#include "Mcp_Plotter.h"

#define LIGHT 299.792458
#define NSTEPMAX 10000
//#define DEBUG

double deltaPhi(double phi1, double phi2);
double deltaR(double eta1, double eta2, double phi1, double phi2);
double DR_xyz(double x, double y, double z);
int    ExtractDummyTime( TH1F *h_Shape );
TH1F** InitTimeLayerHistograms(const char *name, const char *title, int size, int Bin, float Min, float max, string Title, string Mode );
void deleteTimeLayerPlot(TH1F **h, int size);

//Usage: root -b -q .x Mcp_Plotter.C+\(\"../output_RUN738.root\"\) 
void Mcp_Plotter( TString InputFile = "../output.root", TString OutPutFolder = "my_plots" ){
  //Initial Messages
  cout<<"Let's start to do some cool plots!"<<endl;
  MCP_Pos MCP_info;
  InitMCP_Pos( MCP_info );
  //cout<<"Test: "<<MCP_info.SEE.pos[738]<<" "<<MCP_info.Z1.pos[738]<<" "<<MCP_info.MIB2.pos[738]<<endl;
  //Parameters---------------------------------------------------
  bool debug=false;
  int Nplots_single = 8.; //Numbers of first events on which you want a plot
#ifdef DEBUG
  debug=true;
#endif
  setTDRStyle();
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
  std::vector<float> *digi_SeePulse_Index = new vector<float>,    *digi_SeePulse_Value = new vector<float>;
  std::vector<float> *digi_Mib2Pulse_Index = new vector<float>,   *digi_Mib2Pulse_Value = new vector<float>;
  std::vector<float> *digi_Mib3Pulse_Index = new vector<float>,   *digi_Mib3Pulse_Value = new vector<float>;
  std::vector<float> *digi_Zstak1Pulse_Index = new vector<float>, *digi_Zstak1Pulse_Value = new vector<float>;
  std::vector<float> *digi_Zstak2Pulse_Index = new vector<float>, *digi_Zstak2Pulse_Value = new vector<float>;
  Tree->SetBranchAddress( "digi_SeePulse_Index", &digi_SeePulse_Index);
  Tree->SetBranchAddress( "digi_SeePulse_Value", &digi_SeePulse_Value);
  Tree->SetBranchAddress( "digi_Mib2Pulse_Index", &digi_Mib2Pulse_Index);
  Tree->SetBranchAddress( "digi_Mib2Pulse_Value", &digi_Mib2Pulse_Value);
  Tree->SetBranchAddress( "digi_Mib3Pulse_Index", &digi_Mib3Pulse_Index);
  Tree->SetBranchAddress( "digi_Mib3Pulse_Value", &digi_Mib3Pulse_Value);
  Tree->SetBranchAddress( "digi_Zstak1Pulse_Index", &digi_Zstak1Pulse_Index);
  Tree->SetBranchAddress( "digi_Zstak1Pulse_Value", &digi_Zstak1Pulse_Value);
  Tree->SetBranchAddress( "digi_Zstak2Pulse_Index", &digi_Zstak2Pulse_Index);
  Tree->SetBranchAddress( "digi_Zstak2Pulse_Value", &digi_Zstak2Pulse_Value);

  double res_range = 20;
  int res_bins = 2*res_range+1;

  //Single events plots
  TH1F *h_Shape_See, *h_Shape_Mib2, *h_Shape_Mib3, *h_Shape_Z1, *h_Shape_Z2; 
  //Plots on All events
  TH1F *nEv             = new TH1F("nEv","N events, Selec", 3, -0.5, 1.5); nEv->GetXaxis()->SetTitle("#Ev");
  TH1F *Res_SeeMib2     = new TH1F("Res_SeeMib2","Resolution See Mib2", res_bins, -res_range, res_range); Res_SeeMib2->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_SeeMib3     = new TH1F("Res_SeeMib3","Resolution See Mib3", res_bins, -res_range, res_range); Res_SeeMib3->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_SeeZ1       = new TH1F("Res_SeeZ1","Resolution See Z1", res_bins, -res_range, res_range); Res_SeeZ1->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_SeeZ2       = new TH1F("Res_SeeZ2","Resolution See Z2", res_bins, -res_range, res_range); Res_SeeZ2->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Mib2Mib3    = new TH1F("Res_Mib2Mib3","Resolution Mib2 Mib3", res_bins, -res_range, res_range); Res_Mib2Mib3->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Mib2Z1      = new TH1F("Res_Mib2Z1","Resolution Mib2 Z1", res_bins, -res_range, res_range); Res_Mib2Z1->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Mib2Z2      = new TH1F("Res_Mib2Z2","Resolution Mib2 Z2", res_bins, -res_range, res_range); Res_Mib2Z2->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Mib3Z1      = new TH1F("Res_Mib3Z1","Resolution Mib3 Z1", res_bins, -res_range, res_range); Res_Mib3Z1->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Mib3Z2      = new TH1F("Res_Mib3Z2","Resolution Mib3 Z2", res_bins, -res_range, res_range); Res_Mib3Z2->GetXaxis()->SetTitle("Index1 - Index2");
  TH1F *Res_Z1Z2        = new TH1F("Res_Z1Z2","Resolution Z1 Z2", res_bins, -res_range, res_range); Res_Z1Z2->GetXaxis()->SetTitle("Index1 - Index2");
  myc1->cd();

  //LOOP-------
  cout<<"Starting the Loop! Running on: "<<nentries<<" events."<<endl;
  for(Long64_t iEntry=0; iEntry < nentries; iEntry++){
    if( iEntry%1000==0 ) cout<<"You are at the "<<iEntry<<"/"<<nentries<<" event"<<endl;
    stringstream ss;
    ss << iEntry;
    Tree->GetEntry(iEntry);
    h_Shape_See            = new TH1F("h_Shape_See","Pulse Shape SEE", 1024, -0.5, 1023.5); h_Shape_See->GetXaxis()->SetTitle("Index"); h_Shape_See->GetYaxis()->SetTitle("Value");
    h_Shape_Mib2           = new TH1F("h_Shape_Mib2","Pulse Shape MIB2", 1024, -0.5, 1023.5); h_Shape_Mib2->GetXaxis()->SetTitle("Index"); h_Shape_Mib2->GetYaxis()->SetTitle("Value");
    h_Shape_Mib3           = new TH1F("h_Shape_Mib3","Pulse Shape MIB2", 1024, -0.5, 1023.5); h_Shape_Mib3->GetXaxis()->SetTitle("Index"); h_Shape_Mib2->GetYaxis()->SetTitle("Value");
    h_Shape_Z1             = new TH1F("h_Shape_Z1","Pulse Shape Z STAK 1", 1024, -0.5, 1023.5); h_Shape_Z1->GetXaxis()->SetTitle("Index"); h_Shape_Z1->GetYaxis()->SetTitle("Value");
    h_Shape_Z2             = new TH1F("h_Shape_Z2","Pulse Shape Z STAK 2", 1024, -0.5, 1023.5); h_Shape_Z2->GetXaxis()->SetTitle("Index"); h_Shape_Z2->GetYaxis()->SetTitle("Value");
    nEv->SetBinContent(1,nEv->GetBinContent(1)+1);
    //Pulse Shape and Minimum
    int DummyTimeSee(-1), DummyTimeMib2(-1), DummyTimeMib3(-1), DummyTimeZ1(-1), DummyTimeZ2(-1);
    for(unsigned int i=0; i<digi_SeePulse_Index->size(); i++){    if( digi_SeePulse_Value->at(i)>2000 )    h_Shape_See->SetBinContent( digi_SeePulse_Index->at(i), digi_SeePulse_Value->at(i) );}
    for(unsigned int i=0; i<digi_Mib2Pulse_Index->size(); i++){   if( digi_Mib2Pulse_Value->at(i)>2000 )   h_Shape_Mib2->SetBinContent( digi_Mib2Pulse_Index->at(i), digi_Mib2Pulse_Value->at(i) );}
    for(unsigned int i=0; i<digi_Mib3Pulse_Index->size(); i++){   if( digi_Mib3Pulse_Value->at(i)>2000 )   h_Shape_Mib3->SetBinContent( digi_Mib3Pulse_Index->at(i), digi_Mib3Pulse_Value->at(i) );}
    for(unsigned int i=0; i<digi_Zstak1Pulse_Index->size(); i++){ if( digi_Zstak1Pulse_Value->at(i)>2000 ) h_Shape_Z1->SetBinContent( digi_Zstak1Pulse_Index->at(i), digi_Zstak1Pulse_Value->at(i) );}
    for(unsigned int i=0; i<digi_Zstak2Pulse_Index->size(); i++){ if( digi_Zstak2Pulse_Value->at(i)>2000 ) h_Shape_Z2->SetBinContent( digi_Zstak2Pulse_Index->at(i), digi_Zstak2Pulse_Value->at(i) );}
    DummyTimeSee  = ExtractDummyTime(h_Shape_See);
    DummyTimeMib2 = ExtractDummyTime(h_Shape_Mib2);  
    DummyTimeMib3 = ExtractDummyTime(h_Shape_Mib3);
    DummyTimeZ1   = ExtractDummyTime(h_Shape_Z1); 
    DummyTimeZ2   = ExtractDummyTime(h_Shape_Z2);
    
    //Reslution
    if (DummyTimeSee && DummyTimeMib2) Res_SeeMib2->Fill( DummyTimeSee-DummyTimeMib2 );
    if (DummyTimeSee && DummyTimeMib3) Res_SeeMib3->Fill( DummyTimeSee-DummyTimeMib3 );
    if (DummyTimeSee && DummyTimeZ1) Res_SeeZ1->Fill( DummyTimeSee-DummyTimeZ1 );
    if (DummyTimeSee && DummyTimeZ2) Res_SeeZ2->Fill( DummyTimeSee-DummyTimeZ2 );
    if (DummyTimeMib2 && DummyTimeMib3) Res_Mib2Mib3->Fill( DummyTimeMib2-DummyTimeMib3 );
    if (DummyTimeMib2 && DummyTimeZ1) Res_Mib2Z1->Fill( DummyTimeMib2-DummyTimeZ1 );
    if (DummyTimeMib2 && DummyTimeZ2) Res_Mib2Z2->Fill( DummyTimeMib2-DummyTimeZ2 );
    if (DummyTimeMib3 && DummyTimeZ1) Res_Mib3Z1->Fill( DummyTimeMib3-DummyTimeZ1 );
    if (DummyTimeMib3 && DummyTimeZ2) Res_Mib3Z2->Fill( DummyTimeMib3-DummyTimeZ2 );
    if (DummyTimeZ1 && DummyTimeZ2) Res_Z1Z2->Fill( DummyTimeZ1-DummyTimeZ2 );
    
    //Drawning Single Event Histos
    if( iEntry < Nplots_single ){
	TLatex latex; latex.SetTextSize(0.04); latex.SetNDC(); latex.SetTextAlign(13);
	char line[20]; 
	sprintf(line,"Minimum in bin %d", DummyTimeSee ); 
	h_Shape_See->Draw();  latex.DrawLatex(.6,.7,line); TString out = OutPutFolder + "/SingleEvents/PulseShape_See_"+ ss.str() +".png"; myc1->SaveAs( out.Data() );
	sprintf(line,"Minimum in bin %d", DummyTimeMib2 ); 
	h_Shape_Mib2->Draw(); latex.DrawLatex(.6,.7,line); out = OutPutFolder + "/SingleEvents/PulseShape_Mib2_"+ ss.str() +".png"; myc1->SaveAs( out.Data() ); 
	sprintf(line,"Minimum in bin %d", DummyTimeMib3 ); 
	h_Shape_Mib3->Draw(); latex.DrawLatex(.6,.7,line); out = OutPutFolder + "/SingleEvents/PulseShape_Mib3_"+ ss.str() +".png"; myc1->SaveAs( out.Data() ); 
	sprintf(line,"Minimum in bin %d", DummyTimeZ1 ); 
	h_Shape_Z1->Draw();   latex.DrawLatex(.6,.7,line); out = OutPutFolder + "/SingleEvents/PulseShape_Z1_"+ ss.str() +".png"; myc1->SaveAs( out.Data() );
	sprintf(line,"Minimum in bin %d", DummyTimeZ2 ); 
	h_Shape_Z2->Draw();   latex.DrawLatex(.6,.7,line); out = OutPutFolder + "/SingleEvents/PulseShape_Z2_"+ ss.str() +".png"; myc1->SaveAs( out.Data() );
    }
    delete h_Shape_See; delete h_Shape_Mib2; delete h_Shape_Mib3; delete h_Shape_Z1; delete h_Shape_Z2;
  }//All Entries
  //Plots
  myc1->cd();
  nEv->Draw(); gStyle->SetOptStat(0);      TString  out1 = OutPutFolder + "/All_Nevent.png"; myc1->SaveAs( out1.Data() ); delete nEv;
  Res_SeeMib2->Draw(); gStyle->SetOptStat(111111);  out1 = OutPutFolder + "/Res_SeeMib2.png"; myc1->SaveAs( out1.Data() ); delete Res_SeeMib2;
  Res_SeeMib3->Draw(); gStyle->SetOptStat(111111);  out1 = OutPutFolder + "/Res_SeeMib3.png"; myc1->SaveAs( out1.Data() ); delete Res_SeeMib3;
  Res_SeeZ1->Draw(); gStyle->SetOptStat(111111);    out1 = OutPutFolder + "/Res_SeeZ1.png"; myc1->SaveAs( out1.Data() ); delete Res_SeeZ1;
  Res_SeeZ2->Draw(); gStyle->SetOptStat(111111);    out1 = OutPutFolder + "/Res_SeeZ2.png"; myc1->SaveAs( out1.Data() ); delete Res_SeeZ2;
  Res_Mib2Mib3->Draw(); gStyle->SetOptStat(111111); out1 = OutPutFolder + "/Res_Mib2Mib3.png"; myc1->SaveAs( out1.Data() ); delete Res_Mib2Mib3; 
  Res_Mib2Z1->Draw(); gStyle->SetOptStat(111111);   out1 = OutPutFolder + "/Res_Mib2Z1.png"; myc1->SaveAs( out1.Data() ); delete Res_Mib2Z1;  
  Res_Mib2Z2->Draw(); gStyle->SetOptStat(111111);   out1 = OutPutFolder + "/Res_Mib2Z2.png"; myc1->SaveAs( out1.Data() ); delete Res_Mib2Z2;
  Res_Mib3Z1->Draw(); gStyle->SetOptStat(111111);   out1 = OutPutFolder + "/Res_Mib3Z1.png"; myc1->SaveAs( out1.Data() ); delete Res_Mib3Z1;
  Res_Mib3Z2->Draw(); gStyle->SetOptStat(111111);   out1 = OutPutFolder + "/Res_Mib3Z2.png"; myc1->SaveAs( out1.Data() ); delete Res_Mib3Z2;
  Res_Z1Z2->Draw(); gStyle->SetOptStat(111111);     out1 = OutPutFolder + "/Res_Z1Z2.png"; myc1->SaveAs( out1.Data() ); delete Res_Z1Z2; 
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

int ExtractDummyTime(TH1F *h_Shape){
  double Minimum = 99999., Maximum = 0.;
  int    MinimumBin = -1;
  int BinMin(50), BinMax(500);
  for( int i=BinMin; i<BinMax; i++){
    double Cont = h_Shape->GetBinContent( i );
    if( Cont < Minimum ){ Minimum = Cont; MinimumBin = i; }
    if( Cont > Maximum ) Maximum = Cont; 
  }
  
  if (Maximum-Minimum<100) MinimumBin=0;
  
  return MinimumBin;
}
