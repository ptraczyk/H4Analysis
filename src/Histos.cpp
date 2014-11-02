#include "interface/Histos.hpp"
int Histos::BookHisto(string name, string title, int nBins, double xmin, double xmax,string type)
{
	map<string,TH1*>::iterator it;
	it=histoContainer.find(name);
	// if already exist, return
	if ( it!=histoContainer.end() ) return 1;
	// else create it
	if (type== "TH1D") histoContainer[name]=new TH1D(name.c_str(),title.c_str(),nBins,xmin,xmax);
	else if (type == "TProfile") histoContainer[name]=new TProfile(name.c_str(),title.c_str(),nBins,xmin,xmax); 
	return 0;

}
void Histos::FillHisto(string name, double value, double weight)
	{
	histoContainer[name]->Fill(value,weight);
	}
void Histos::FillProfile(string name, double x,double y, double weight)
	{
	//cout<<"[Histos]::[FillProfile]"<<name<<endl; //DEBUG
	dynamic_cast<TProfile*>(histoContainer[name])->Fill(x,y,weight);
	}
void Histos::Write()
	{
	map<string,TH1*>::iterator it;
	for( it=histoContainer.begin(); it!=histoContainer.end() ;it++)
		{
		it->second->Write();
		}
	return;
	}
