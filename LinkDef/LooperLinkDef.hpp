#ifndef LOOPER_H
#define LOOPER_H

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include <iostream>
#include "interface/BaseAnalysis.hpp"
#include "interface/Event.hpp"
using namespace std;


class Looper : public tree {
friend class BaseAnalysis;

private:
	TChain *fChain;
	string chainName;

	void SetBranchesH4tree();
	void SetBranchesOuttree();
	void SetBranchesCommon();
	
	map<string,bool> activeBranches;	
public:
	Looper(){ fChain=NULL; chainName="";};
	~Looper(){};
	void AddToChain(string fileName);	
	void Init();
	void SetBranches(string tree="H4tree");
	template<class T>
	void SetBranchAddress(string name,T ptr);
	inline void GetEntry( ULong64_t iEntry){ fChain->GetEntry(iEntry);};

};

// TEMPLATE SHOULD stay in the .H file
template<class T>
void Looper::SetBranchAddress(string name,T ptr)
{
  fChain->SetBranchAddress(name.c_str(),ptr); 
  if ( !activeBranches.empty() )
	{
	map<string,bool>::iterator it;
	it=activeBranches.find(name);
	if (it != activeBranches.end() ){
		fChain->SetBranchStatus(name.c_str(),1);
 		isFilled[name]=1; 
  		cout<<"* Setting Branch Address For Branch:"<<name<<endl;
		}
	}
  else
	{
 	isFilled[name]=1; 
  	cout<<"* Setting Branch Address For Branch:"<<name<<endl;
	}
}

#endif

