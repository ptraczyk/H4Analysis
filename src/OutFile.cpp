#include "interface/OutFile.hpp"
void OutFile::Init()
{
	if(fOut==NULL) fOut=TFile::Open(outFileName.c_str(),"RECREATE");
	return;
}
void OutFile::Close(){
	if(fOut !=NULL ) fOut->Close();
	fOut=NULL;
	return;
}
