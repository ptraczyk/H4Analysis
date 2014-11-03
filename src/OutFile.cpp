#include "interface/OutFile.hpp"
#include <iostream>
using namespace std;

void OutFile::Init()
{
	if(fOut==NULL) cout<<"[OutFile]::[Init] Opening file"<<outFileName<<endl;
	if(fOut==NULL) fOut=TFile::Open(outFileName.c_str(),"RECREATE");
	return;
}
void OutFile::Close(){
	if(fOut !=NULL ) fOut->Close();
	fOut=NULL;
	return;
}
