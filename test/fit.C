#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TCanvas.h"
#include <vector>

using namespace std;


void FitLinear(TGraph *g, int firstN,double &a,double&b, double&chidiff) // ax+b:
{
	TGraph *g2=new TGraph();	
	g2->SetName( Form("%s_fit_%d",g->GetName(),firstN));
	double x;double y;
	double minX=-10000;
	double maxX=-10000;
	for(int i=0;i<firstN;++i)
		{
		g->GetPoint(i,x,y);
		g2->SetPoint(i,x,y);
		if (i==0 || x<minX) minX=x;
		if (i==0 || x>maxX) maxX=x;
		
		}
	TF1 line("line","[0]+x*[1]",minX-.1,maxX+.1);
	TF1 pol("pol","[0]+x*[1]+x*x*[2]",minX-.1,maxX+.1);
	cout <<" MIN/MAX X="<<minX<<" "<<maxX<<endl;
	
	g2->Fit(&line,"WQNSF+","goff");
	g2->Fit(&pol ,"WQNSF+","goff");

	double chi2= line.GetChisquare();
		b=line.GetParameter(0);
		a=line.GetParameter(1);
	double chi2_2 = pol.GetChisquare();
	chidiff=chi2_2-chi2;
	double p1=firstN-2;
	double p2=firstN-3;
	double f =  ((chi2 - chi2_2)/(p1-p2)  )/ ( chi2_2/ (firstN-p2));
	prob=0;
	if (chi2_2 == 0 ) return;
	cout<<"Debug Line:"<<firstN<<":"<<chi2<<":"<<chi2_2<<":"<<p1<<":"<<p2<<"|"<<f<<endl;
	prob= (1.-TMath::FDistI(f,p1-p2,firstN-p2) )*100;
	cout<<"Quadratic Improvement for "<< firstN <<" is "<< prob <<"% "<<endl;
}

void GausIterate(TH1 *h,TF1*f,float z=2)
{
	//iterate a gaussian fit, one times in a range of sigma
	double mean=f->GetParameter(1);
	double sigma=f->GetParameter(2);
	f->SetRange( mean-z*sigma,mean+z*sigma);
	f->SetParLimits(1, mean*.75,mean*1.5);
	f->SetParLimits(2, sigma*.5, sigma*2);
	h->Fit(f,"WQRN");
	h->Fit(f,"WQRNM");
	return;
}

double GausFit(TH2D *h2, TProfile *p, double hv  )
{
	cout<<"[GausFit]"<<h2<<" "<<p<<" "<<hv<<endl;
	TCanvas *c=new TCanvas(  Form("c_hv%.0lf",hv),"c");

	// X = HV ; Y= adc
	int hVBin= h2->GetXaxis()->FindBin(hv);
	TH1D *h=h2->ProjectionY("_py", hVBin,hVBin);
	//estimate the mean from the profile
	double mean=p->GetBinContent(p->FindBin(hv) );
	TF1 *gaus=new TF1("myfunc","gaus",h2->GetYaxis()->GetBinLowEdge(1), h2->GetYaxis()->GetBinLowEdge( h2->GetYaxis()->GetNbins()+1 ) );
	// 0 is norm	
	// mean
	gaus->SetParameter(1,mean);
	gaus->SetParLimits(1,mean*.75,mean*1.5);
	//sigma
	gaus->SetParameter(2,mean*.1);
	gaus->SetParLimits(2,mean*.01,mean*1);
	h->Fit(gaus,"WQN");
	h->Fit(gaus,"WQNM");
	// --- iterate 2s
	 GausIterate(h,gaus,3);
	 GausIterate(h,gaus,3);
	 GausIterate(h,gaus,3);
	
	h->SetMarkerStyle(20);
	h->DrawClone("P");
	gaus->DrawClone("L SAME");
	
	return gaus->GetParameter(1);

}

void fit(int ch=0,const string what="chint"){
	//TFile *f=TFile::Open("plot.root");
	TFile *f=TFile::Open("physics_11_6.root");
	f->cd();
	//string what="chint";
	//string what="maxampl";
	//TProfile *prof=gDirectory->Get("tprofile_chint_sub_ch0_E20");
	TProfile *prof=(TProfile*)gDirectory->Get(Form("tprofile_%s_sub_ch%d_E20",what.c_str(),ch));
	//th2d_chint_sub_ch0_E20
	TH2D 	 *h2=(TH2D*)gDirectory->Get(Form("th2d_%s_sub_ch%d_E20",what.c_str(),ch));

	prof->SetMarkerStyle(20);
	TGraph *g=new TGraph();
	g->SetName(Form("tofit_ch%d",ch));
	//
	vector<int> HV; 
		if(what !="maxampl")HV.push_back(600);
		if(what != "chint")HV.push_back(650);
		HV.push_back(700);
		HV.push_back(750);
		HV.push_back(800);
		HV.push_back(850);
		HV.push_back(900);
		HV.push_back(950);
		HV.push_back(1000);
		HV.push_back(1050);
		HV.push_back(1100);
		HV.push_back(1150);
		HV.push_back(1200);
		HV.push_back(1250);
		HV.push_back(1300);
		HV.push_back(1350);
		HV.push_back(1400);
	
	// --- for(int i=0;i<HV.size();++i)g->SetPoint( i, HV[i], prof->GetBinContent( prof->FindBin(HV[i])) ); // NON LOG
	//for(int i=0;i<HV.size();++i)g->SetPoint( i, TMath::Log(HV[i]), TMath::Log( prof->GetBinContent( prof->FindBin(HV[i])) ) ); // LOG-LOG, from prof
	//FROM FIT LOG LOG
	for(int i=0;i<HV.size() ; ++i){g->SetPoint(i, TMath::Log(HV[i]) ,TMath::Log(GausFit(h2, prof, double(HV[i]))  ) ) ;}
	
	g->SetMarkerStyle(20);
	g->Draw("AP");
	
	//convert the TGraph to a spline 
	TSpline *spl=new TSpline3(Form("spline_ch%d",ch),g);
	
	TGraph *spl_gr=new TGraph();
	spl_gr->SetName("myspline_graph");
	for (float x=6;x<8;x+=0.01)spl_gr->SetPoint(spl_gr->GetN(),x,spl->Eval(x));

	TCanvas *c=new TCanvas("c","c",800,800);	
	TH2D *dummy=new TH2D("dummy","dummy",100,6,8,100,-10,40);
	dummy->Draw("AXIS");
	spl_gr->Draw("L SAME");
	g->Draw("P SAME");

	double a,b,chidiff	;
	//FitLinear(g,2,a,b,chidiff);
	TF1 line(Form("line_ch%d",ch),"pol1",6,8);
	// chidiff/N >0.001 fail
	FitLinear(g,3,a,b,chidiff);
		line.SetTitle(Form("3 -- %f",chidiff));line.SetLineColor(kRed); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
	FitLinear(g,4,a,b,chidiff);
		line.SetTitle(Form("4 -- %f",chidiff));line.SetLineColor(kBlue); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
		if (what == "chint"){
			TFile *out=TFile::Open("chintCorr1.root",(ch==0)?"RECREATE":"UPDATE");
			out->cd();
			line.Write();
			g->Write();
			spl->Write();
			out->Close();
		}
	FitLinear(g,5,a,b,chidiff);
		line.SetTitle(Form("5 -- %f",chidiff));line.SetLineColor(kGreen+2); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
	FitLinear(g,6,a,b,chidiff);
		line.SetTitle(Form("6 -- %f",chidiff));line.SetLineColor(kOrange); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
	FitLinear(g,7,a,b,chidiff);
		line.SetTitle(Form("7 -- %f",chidiff));line.SetLineColor(kRed+2); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
	FitLinear(g,8,a,b,chidiff);
		line.SetTitle(Form("8 -- %f",chidiff));line.SetLineColor(kBlue+2); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
		if (what == "maxampl"){
			TFile *out=TFile::Open("maxamplCorr1.root",(ch==0)?"RECREATE":"UPDATE");
			out->cd();
			line.Write();
			g->Write();
			spl->Write();
			out->Close();
		}
	FitLinear(g,9,a,b,chidiff);
		line.SetTitle(Form("9 -- %f",chidiff));line.SetLineColor(kMagenta); line.SetParameter(0,b); line.SetParameter(1,a) ; line.DrawCopy("L SAME");
	c->ls();


}
