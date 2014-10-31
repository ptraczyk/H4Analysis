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
	Filler(){};
	~Filler(){};
	void Init();
	void Close();
	void SetBranches(); // DO NOT PUT THIS VIRTUAL
	void SetBranchAddress();
	//template<class T>
	//void SetBranchAddress(string name,T ptr);
	void SetBranchAddress(string name,ULong64_t* ptr);
	void SetBranchAddress(string name,UInt_t* ptr);
	void SetBranchAddress(string name,Int_t* ptr);
	void SetBranchAddress(string name,Float_t* ptr);
	void SetBranchAddress(string name,Double_t* ptr);
	void SetBranchAddress(string name,vector<Float_t>** ptr);
	void SetBranchAddress(string name,vector<UInt_t>** ptr);
	void SetBranchAddress(string name,vector<Int_t>** ptr);
	void SetBranchAddress(string name,vector<bool>** ptr);
	void SetBranchAddress(string name,vector<ULong64_t>** ptr);
	inline void Fill( ){ fChain->Fill() ;};

};

// --- #ifndef FILLER_CPP
// --- template<class T>
// --- void SetBranchAddress(string name,T ptr);
// --- 	{
// ---   	cout<<"[Filler]::[ERROR]: Unable to handle Branch "<<name<<endl;
// ---  	assert(0);
// --- 	};
// --- #endif

#endif
