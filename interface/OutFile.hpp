#ifndef OUTFILE_H
#define OUTFILE_H

#include "TFile.h"
#include <string>
using namespace std;

class OutFile{
protected:
	TFile *fOut;
public:
	string outFileName;
	void Init();
	void Close();
	OutFile(){ fOut=NULL;};
	~OutFile(){Close();};
};

#endif
