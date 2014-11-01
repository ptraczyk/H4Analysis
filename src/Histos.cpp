#include "interface/Histos.hpp"
int Histos::BookHisto(string name, string title, int nBins, double xmin, double xmax)
{
	map<string,TH1D*>::iterator it;
	it=histoContainer.find(name);
	// if already exist, return
	if ( it!=histoContainer.end() ) return 1;
	// else create it
	histoContainer[name]=new TH1D(name.c_str(),title.c_str(),nBins,xmin,xmax);
	return 0;

}
void Histos::Fill(string name, double value, double weight)
	{
	histoContainer[name]->Fill(value,weight);
	}
void Histos::Write()
	{
	map<string,TH1D*>::iterator it;
	for( it=histoContainer.begin(); it!=histoContainer.end() ;it++)
		{
		it->second->Write();
		}
	return;
	}
