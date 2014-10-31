#ifndef FILLER_H
#define FILLER_H

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include <iostream>
#include "interface/Event.hpp"
#include <assert.h>
using namespace std;

class Filler { // if I inheriths from tree: diamond of deaths
friend class BaseAnalysis;

protected:
	TFile *fOut;
	TTree *fChain;	
	tree out;

	string chainName;
	string outFileName;
	void SetBranchesH4tree();
	void SetBranchesOuttree();
	void SetBranchesCommon();
	map<string,bool> activeBranches;	
	bool isActive(string name);
public:
	void Init();
	void Close();
	void SetBranches(); // DO NOT PUT THIS VIRTUAL
	void SetBranchAddress();
	template<class T>
	void SetBranchAddress(string name,T ptr);
	inline void Fill( ){ fChain->Fill() ;};

};

bool Filler::isActive(string name)
{
	map<string,bool>::iterator it;
	it=activeBranches.find(name);
	if (it == activeBranches.end() ) return false;
	else return activeBranches[name];
}

// -------------------------- TEMPLATE SPECIFICATION ----------- 
// --- VECTOR ----
template<>
void Filler::SetBranchAddress(string name, vector<UInt_t>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<UInt_t>",ptr);	
	out.isFilled[name]=1;
}
template<>
void Filler::SetBranchAddress(string name, vector<Int_t>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<Int_t>",ptr);	
	out.isFilled[name]=1;
}
template<>
void Filler::SetBranchAddress(string name, vector<Float_t>** ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(name.c_str(),"vector<Float_t>",ptr);	
	out.isFilled[name]=1;
}
// ---- VALUES ---
template<>
void Filler::SetBranchAddress(string name, UInt_t* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/i",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
template<>
void Filler::SetBranchAddress(string name, Int_t* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/I",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
template<>
void Filler::SetBranchAddress(string name, Float_t* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/F",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
template<>
void Filler::SetBranchAddress(string name, Double_t* ptr)
{
	if (!isActive(name) ) return;
	fChain->Branch(Form("%s/D",name.c_str()),ptr);	
	out.isFilled[name]=1;
}
/// ---------- GENERIC
template<class T>
void Filler::SetBranchAddress(string name,T ptr)
{
  cout<<"[Filler]::[ERROR]: Unable to handle Branch "<<name<<endl;
  assert(0);
}


#endif
