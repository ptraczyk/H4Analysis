#include "interface/OutFile.hpp"
#include "TH1I.h"
#include "TNamed.h"
#include <iostream>
using namespace std;

void OutFile::Init()
{
	if(fOut==NULL) cout<<"[OutFile]::[Init] Opening file"<<outFileName<<endl;
	if(fOut==NULL) fOut=TFile::Open(outFileName.c_str(),"RECREATE");
	ReadTag("bin/tag.txt");
	fOut->cd();
	//TH1I tagN("tag",tag.c_str(),1,0,1); //TH1 are haddable, TNamed will be saved all
	TNamed tagN("tag",tag.c_str()); //TH1 are haddable, TNamed will be saved all
	tagN.Write();	
	return;
}
void OutFile::Close(){
	if(fOut !=NULL ) fOut->Close();
	fOut=NULL;
	return;
}

#include <cstdio>
void OutFile::ReadTag(string fname){
	FILE *in=fopen(fname.c_str(),"r");
	if (in==NULL) tag="None";
	char buffer[1024];
	fscanf(in,"%s",&buffer);
	tag=buffer;
	fclose(in);
	return;
}














