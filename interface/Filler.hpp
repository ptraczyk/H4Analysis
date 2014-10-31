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

	void SetBranchesH4tree();
	void SetBranchesOuttree();
	void SetBranchesCommon();
	map<string,bool> activeBranches;	
	bool isActive(string name);
	// ---------
	void SetBranchAddress(string name,unsigned long long* ptr);
	void SetBranchAddress(string name,unsigned int* ptr);
	void SetBranchAddress(string name,int* ptr);
	void SetBranchAddress(string name,float* ptr);
	void SetBranchAddress(string name,double* ptr);

	void SetBranchAddress(string name,vector<float>** 	ptr);
	void SetBranchAddress(string name,vector<double>** 	ptr);
	void SetBranchAddress(string name,vector<unsigned int>** ptr);
	void SetBranchAddress(string name,vector<int>** 	ptr);
	void SetBranchAddress(string name,vector<bool>** 	ptr);
	void SetBranchAddress(string name,vector<unsigned long long>** ptr);
public:
	string chainName;
	string outFileName;
	Filler(){};
	~Filler(){};
	void Init();
	void Close();
	void SetBranches(); // DO NOT PUT THIS VIRTUAL
	void SetBranchAddress();
	//template<class T>
	//void SetBranchAddress(string name,T ptr);

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
