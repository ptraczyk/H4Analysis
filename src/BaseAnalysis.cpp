#include "interface/BaseAnalysis.hpp"

void BaseAnalysis::Loop(){};
void BaseAnalysis::Init(LoopAndFill*l1) 
	{ 
	cout<<"[BaseAnalysis]::[Init]"<<endl;
	l = l1 ;
	cout<<"[BaseAnalysis]::[Init]::Done"<<endl;
	return;
	}
void BaseAnalysis::AnalyzeEvent(){}

