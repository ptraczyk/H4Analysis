#ifndef OUTFILE_H
#define OUTFILE_H

#include "TFile.h"
#include <string>
using namespace std;

class OutFile{
protected:
	TFile *fOut;
	void ReadTag(string fname);
public:
	string outFileName;
	string tag;
	void Init();
	void Close();
	OutFile(){ fOut=NULL;};
	~OutFile(){Close();};
};

#endif
