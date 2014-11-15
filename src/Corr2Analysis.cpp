//#define VERBOSE_CORR2

#include "interface/Corr2Analysis.hpp"

#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TLatex.h"

#define LN2 6.93147180559945286e-01


// solve equation mx+q == Ae^{-x/tau}
double Corr2Analysis::solve(double m , double q , double A ,double tau,double x,double epsilon,int iteration)
{
        // metodo delle tangenti. Il piu' veloce.
        double y=A*TMath::Exp(-x/tau)-m*x-q;
        //cout<<" Iteration for solve: y="<< y <<" m="<<m<<" q="<<q<<" A="<<A<<" tau="<<tau<< " x="<<x <<" Exp="<<double(A*TMath::Exp(-x/tau)) << " line="<<m*x+q<<endl;
        if ( abs(y)< epsilon) return x;
        double m1=A*(-1./tau)*TMath::Exp(-x/tau) -m;
        double q1=y-m1*x;
        double x1= -q1/m1;
        //cout<<"Iteration for solve: x -> x1 "<<x1<< " m1="<<m1<<" q1="<<q1<<endl;
        if (iteration>20) {
		cout<<"SOLVE DIDN'T FOUND A SOLUTION"<<endl;
		return x1; // didn' converge
		}
        return solve(m,q,A,tau,x1,epsilon,iteration+1);
}


void Corr2Analysis::ClearEvent()
{
	l->digi_charge_integrated_corr2->clear();
	l->digi_max_amplitude_corr2->clear();
	resetHistos(); // double called , but second time is just a check
#ifdef VERBOSE_CORR2
	mywatch.Reset();
#endif
}

void Corr2Analysis::AnalyzeEvent()
{
	getHistos();

	for( unsigned int iCh=0;iCh<unsigned(nChannels);++iCh)
	      {
		TH1D *h=myhistos[iCh];
		pair<double,double> Area=fit(h);
		l->digi_max_amplitude_corr2->push_back(Area.first); // this is NOT A MAX AMPL
		l->digi_charge_integrated_corr2->push_back(Area.second); // 
	      }
	resetHistos(); // this should delete everything

}

void Corr2Analysis::Init(LoopAndFill *l1)
{
	BaseAnalysis::Init(l1);
	// check that these branches are input
	return;
}

void Corr2Analysis::Close(){
	resetHistos();
}

void Corr2Analysis::resetHistos(){
	for(unsigned int i=0;i<myhistos.size();++i)
		{
		delete myhistos[i];
		}
	myhistos.clear();
}

void Corr2Analysis::getHistos(){
//get the TH1D from the current event of the channel i
	resetHistos();	
	for(int iCh=0;iCh<nChannels;++iCh)
		{
		TH1D *h=new TH1D(Form("digi_ch%d_evt%d",iCh,l->evtNumber),"myDigiHisto",1024,0-.5,1024-.5);
		myhistos.push_back(h);
		}
	for (int iSample=0;iSample<l->nDigiSamples;++iSample)
		{
		UInt_t iCh=l->digiChannel[iSample];
		if(iCh >= nChannels) continue;
		float y=-l->digiSampleValueSub[iSample];	 //they are negative
		UInt_t x=l->digiSampleIndex[iSample];
		myhistos[iCh]->SetBinContent(myhistos[iCh]->FindBin(x),y);
		}
	// subtract local pedestal: first 5-45 elements
	for(int iCh=0;iCh<nChannels;++iCh)
		{
		int n=0;
		double S=0.;
		double S2=0.; // for variance
		for(int i=5;i<45;++i){ S+=myhistos[iCh]->GetBinContent(i);++n; S2+=TMath::Power(myhistos[iCh]->GetBinContent(i),2);}
		S/=n;
		S2/=n;
		S2=TMath::Sqrt(S2-S*S);
		for(int i=1;i<=myhistos[iCh]->GetNbinsX();++i)
			{
			double y=myhistos[iCh]->GetBinContent(i)-S;
			myhistos[iCh]->SetBinContent(i,y);
			myhistos[iCh]->SetBinError(i,S2);
			}
		}
	return ;
}


pair<double,double> Corr2Analysis::fit(TH1D*h)
{
// find max-ampl
        int iMax=0; float yMax=-999.,xMax=0;
        for(int i=1;i<=h->GetNbinsX();++i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if( i==1 || y>yMax) {yMax=y; iMax=i;xMax=x;}
                }
        // find 10% 50% points  --> will be used for fit ranges
        int i10_1=0,i10_2=1000,i50_1=0,i50_2=1000;
        for(int i=1;i<iMax;++i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if ( (x<xMax) && (y<yMax*.1) ) i10_1=i;
                if ( (x<xMax) && (y<yMax*.5) ) i50_1=i;
                }
        for(int i=h->GetNbinsX();i>iMax;--i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if ( (x>xMax) && (y<yMax*.1) ) i10_2=i;
                if ( (x>xMax) && (y<yMax*.5) ) i50_2=i;
                }
	// put iMax in a center like position
	if (iMax<=45 ) iMax=50; // 3-45 circa pedestal
	if (iMax>900 ) iMax=50; // >900 = end
	// put boundaries on fractional positions
	if (i50_1 < 45)   i50_1 = 49;
	if (i50_1>=iMax)  i50_1=iMax-1;
	if (i10_1 < 40)   i10_1 = 45;
	if (i10_1>=i50_1) i10_1=i50_1-1;
	//
	if ( i50_2 > 900 ) i50_2 = 900;
	if ( i50_2<= iMax) i50_2= iMax+1;
	if ( i10_2 > 900 ) i50_2 = 901;
	if ( i10_2<= i50_2)i50_2= i50_2+1;
#ifdef VERBOSE_CORR2
	cout<<"[VERBOSE_CORR2]: fit on histo:"<<h->GetName()<<endl;
	cout <<"[VERBOSE_CORR2]: i10_1,i50_1,iMax,i50_2,i10_2,yMax ="
			<<i10_1<<","
			<<i50_1<<","
			<<iMax<<","
			<<i50_2<<","
			<<i10_2<<","
			<<yMax<<endl;
	mywatch.Start();
#endif
	 double l1=h->GetBinCenter(i10_1),l2=h->GetBinCenter(i50_1);

        TF1 *line=new TF1("line","pol1",l1,l2);
        line->SetLineColor(kBlue);
        h->Fit(line,"WQR");
        h->Fit(line,"WQRM");
        double q=line->GetParameter(0);
        double m=line->GetParameter(1);
        for(int i=i10_1-1;i>=0;--i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if (abs(y-(m*x+q))>tolerance ) break;
                l1=x;
                }
        for(int i=i50_1+1;i<iMax;++i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if (abs(y-(m*x+q))>tolerance ) break;
                l2=x;
                }
	if( fabs(l1-l2)<3.) // too small
		{
		l1-=1.;
		l2+=1.;
		}
        line->SetRange(l1,l2);
        h->Fit(line,"QR");
        h->Fit(line,"QRM");
        q=line->GetParameter(0);
        m=line->GetParameter(1);
#ifdef VERBOSE_CORR2
	mywatch.Stop();
	cout<<" line fitted: m="<<m<<" q="<<q<<endl;
	cout<<" LINE TAKE="<<mywatch.CpuTime()<<endl;
	mywatch.Start();
#endif
       double r1=h->GetBinCenter(i50_2);
       double r2=h->GetBinCenter(i10_2);
        TF1 *f=new TF1("expo","expo",r1,r2);
        f->SetParameter(1, -LN2/(i50_2-iMax) ); f ->SetParLimits(1,-1.e-5 ,-LN2/(i50_2-iMax)*10 );
#ifdef VERBOSE_CORR2
	cout<<" VERBOSE_CORR2: RANGE EXPO [i50_2,i10_2]="<<r1<<","<<r2<<endl;
	cout <<" VERBOSE: PREFIT: tau ="<<-1./f->GetParameter(1)<<" IN ["<<(i50_2-iMax)/(10.*LN2)<<","<<1./1.e-5 <<"]"<<endl;
#endif
        h->Fit(f,"WQR");
        h->Fit(f,"WQRM");
#ifdef VERBOSE_CORR2
	cout<<"[VERBOSE_CORR2]: FIT STEP1"<<endl;
#endif
        //cout << "EXPO RANGE 1 "<< r1<< " : "<<r2<<endl;
        for(int i=i50_2-1;i>=iMax;--i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if (abs(y-f->Eval(x))>tolerance ) break;
                r1=x;
                }
        for(int i=i10_2+1;i<=h->GetNbinsX();++i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if (abs(y-f->Eval(x))>tolerance ) break;
                r2=x;
                }
        //cout << "EXPO RANGE 2 "<< r1<< " : "<<TMath::Min(r2,1000.)<<endl;
        f->SetRange(r1,1000.);
#ifdef VERBOSE_CORR2
	cout<<"[VERBOSE_CORR2]: FIT STEP1 part2"<<endl;
#endif
        h->Fit(f,"QR");
        h->Fit(f,"QRM");
#ifdef VERBOSE_CORR2
	cout<<"[VERBOSE_CORR2]: FIT STEP2"<<endl;
#endif
	if (f->GetChisquare() / f->GetNDF() > 50.)
		{
		#ifdef VERBOSE_CORR2
			cout<<"[VERBOSE_CORR2]:  BAD CHI2, REFIT"<<endl;
		#endif
		TH1D *h_c=(TH1D*)h->Clone("myclone");
		h_c->Rebin(4); h_c->Scale(1./4.);
        	f->SetRange(iMax+(r1-iMax)*.1,1000.); //try to extend range
        	h_c->Fit(f,"QR");
       	 	h_c->Fit(f,"QRM");
		if (f->GetChisquare() / f->GetNDF() > 50.){ // try to reduce the range
		#ifdef VERBOSE_CORR2
			cout<<"[VERBOSE_CORR2]:  BAD CHI2, REFIT AGAIN"<<endl;
		#endif
        		f->SetRange(r1+ (1000.-r1)*.15,1000.); //try to extend range
        		h_c->Fit(f,"QR");
       	 		h_c->Fit(f,"QRM");
		}
		h_c->Delete();
		}

        double x0= -q/m;

        double A=TMath::Exp(f->GetParameter(0));
        double tau=-1./f->GetParameter(1);
	
#ifdef VERBOSE_CORR2
	mywatch.Stop();
	cout<<" expo fitted: A="<<A<<" tau="<<tau<<endl;
	cout<<" EXPO FIT take :"<< mywatch.CpuTime()<<endl;
	mywatch.Start();
#endif
	TF1 *test=new TF1("expo_mod","[0]*(1.+[2]/x)*TMath::Exp(-x/[1])",r1 - (r1-xMax)/2.,TMath::Min(r2*2,1000.));
        test->SetParameter(0,A); test->SetParLimits(0,0,100*A);
        test->SetParameter(1,tau); test->SetParLimits(1,.2*tau,20*tau);
        test->SetParameter(2,0.0);
	if (test->GetChisquare() / test->GetNDF() > 50.)
		{
		TH1D *h_c=(TH1D*)h->Clone("myclone");
		h_c->Rebin(4); h_c->Scale(1./4.);
		double r=r1 - (r1-xMax)/2.;
        	test->SetRange(r + (1000.-r)*.15,1000.); // remove 15% of the fit range
        	h_c->Fit(test,"QR");
       	 	h_c->Fit(test,"QRM");
		h_c->Delete();
		if(test->GetChisquare() / test->GetNDF() > 50) //try to extend
			{
        		test->SetRange(iMax+1,1000.); // remove 15% of the fit range
        		h_c->Fit(test,"QR");
       		 	h_c->Fit(test,"QRM");
			}
		}
        h->Fit(test,"QR");
        h->Fit(test,"QRM");

	if( f->GetChisquare()/f->GetNDF() >50 ) {
		#ifdef VERBOSE_CORR2
		cout<<"[VERBOSE_CORR2]: Bad CHI2: LastHope use test results"<<endl;
		#endif
		double r=fabs(test->GetParameter(2)/tolerance);
		if ( r> 600) r=600;
        	f->SetRange( r,1000.); 
		f->SetParameter(0,TMath::Log(test->GetParameter(0)));	
		f->SetParameter(1,-1./test->GetParameter(1));
		h->Fit(f,"QR");
		h->Fit(f,"QRM");
        	A=TMath::Exp(f->GetParameter(0));
        	tau=-1./f->GetParameter(1);
		}
	// last hope	
	if( f->GetChisquare()/f->GetNDF() >50 ) {
		#ifdef VERBOSE_CORR2
		cout<<"[VERBOSE_CORR2]: Bad CHI2: LastHope fit"<<endl;
		#endif
		TH1D *h_log=log(h);
		f->SetRange(r1,1000);	
		TF1 *line2=new TF1("line2","pol1",r1,1000);	
		h_log->Fit(line2,"WQR");
		f->SetParameter(0,line2->GetParameter(0));
		f->SetParameter(1,line2->GetParameter(1));
		double chi2=h->Chisquare(f,"R");
		f->SetChisquare(chi2);
		f->SetNDF(line2->GetNDF());
		delete h_log;
		delete line2;
		}

        const int N1=3;
        double x1=h->GetBinCenter(iMax);
        for(int i=i50_2-1,icount=0;i>=iMax;--i)
                {
                //double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                double y2=test->Eval(x);
                double yF=f->Eval(x);
                //cout<<"Evaluating X1: x="<<x<<" y2="<<y2<<" yF="<<yF<<" %=abs(y2-yF)/yF="<<fabs(y2-yF)/fabs(yF)<<endl;
                if (fabs(y2-yF)/fabs(yF) > tolerance ) icount++;
                else icount=0;
                if(icount >=N1 )
                        {
                        x1=h->GetBinCenter(i+N1-1);
                        break;
                        }
                }

#ifdef VERBOSE_CORR2
	mywatch.Stop();
	cout<<"[VERBOSE_CORR2]: TEST FIT TAKE:"<<mywatch.CpuTime()<<endl;
	cout<<"[VERBOSE_CORR2]: CHI2/NDF: LINE "<<line->GetChisquare() / line->GetNDF() 
				<< " EXPO "<<f->GetChisquare()/f->GetNDF()
				<< " TEST "<<test->GetChisquare()/test->GetNDF()<<endl;
				
	mywatch.Start();
#endif
        double x2=solve(m,q,A,tau);
#ifdef VERBOSE_CORR2
	mywatch.Stop();
	cout<<" SOLVE TAKE:"<<mywatch.CpuTime()<<endl;
	TCanvas *c=new TCanvas("c","c",600,600);
		h->Draw("P");
		h->GetYaxis()->SetRangeUser(-yMax*.1,yMax*1.2);
		f->Draw("LSAME");
		test->SetLineColor(kGreen+1);test->Draw("LSAME");
		line->Draw("LSAME");
		DrawLine(x0,0,x0,yMax);	
		DrawLine(x1,0,x1,yMax);	
		DrawLine(x2,0,x2,yMax);	
		DrawLine(0,yMax,1000,yMax);	
		DrawLine(0,yMax*.1,1000,yMax*.1);	
		DrawLine(0,yMax*.5,1000,yMax*.5);	
		//check if test is better
	TF1 *test2=new TF1("expo_mod2","[0]*TMath::Exp(-x/[1])",r1 - (r1-xMax)/2.,TMath::Min(r2*2,1000.));
        test2->SetParameter(0,test->GetParameter(0));
        test2->SetParameter(1,test->GetParameter(1));
	test2->SetLineColor(kMagenta);
	test2->Draw("LSAME");
		TLatex *lat=new TLatex() ; lat->SetNDC();lat->SetTextAlign(22);
		lat->DrawLatex(.7,.55,Form("Line #chi^{2}/NDF=%.2f",line->GetChisquare() / line->GetNDF()));
		lat->DrawLatex(.7,.50,Form("Expo #chi^{2}/NDF=%.2f",f->GetChisquare() / f->GetNDF()));
		lat->DrawLatex(.7,.45,Form("Test #chi^{2}/NDF=%.2f",test->GetChisquare() / test->GetNDF()));
		lat->DrawLatex(.7,.40,Form("Test 3rd= %.2f",test->GetParameter(2)));
		TPad *p=new TPad("p","p",.65,.74,.95,.95);
		p->Draw(); p->cd(); 
		TH1D *hc=(TH1D*)h->Clone(Form("%s_clone",h->GetName()));
		hc->Draw("P"); hc->GetYaxis()->SetRangeUser(0.1,yMax*10);
		p->SetLogy();
		f->Draw("LSAME");
		line->Draw("LSAME");
		
		c->SaveAs(Form("verbose/fit_run%u_evt%u_%s.png",l->runNumber,l->evtNumber,h->GetName()));
		lat->Delete();
		hc->Delete();
		p->Delete();
		c->Delete();
		test2->Delete();
	mywatch.Start(kFALSE);
#endif
        double area0=0.5*(x2-x0)*(x2-x0)*m + A*tau*TMath::Exp(-x2/tau);

        double A1=(m*x1+q)/TMath::Exp(-x1/tau);
        double area1=0.5*(x1-x0)*(x1-x0)*m + A1*tau*TMath::Exp(-x1/tau);

	pair<double,double> R(area0,area1);
	
#ifdef VERBOSE_CORR2
	mywatch.Stop();
	cout<<" x0="<<x0<<" x1="<<x1<<" x2="<<x2<<" A0="<<area0<<" A1="<<area1<<endl;
	cout<<" MATH TAKE:"<<mywatch.CpuTime()<<endl;
#endif
	if(f->GetChisquare() / f->GetNDF() >100. || line->GetChisquare() / line->GetNDF()> 100. || test->GetChisquare() / test->GetNDF() >100)
		{ R.first=-999.; R.second=-999.;}
	//delete everything you constructed
	delete line;
	delete f;
	delete test;
	return R;
}

#ifdef VERBOSE_CORR2
void Corr2Analysis::DrawLine(float x1,float y1, float x2,float y2)
{
 TGraph *g=new TGraph();
	g->SetName("Line");
	g->SetLineWidth(2);
	g->SetPoint(0,x1,y1);
	g->SetPoint(1,x2,y2);
	g->DrawClone("LSAME");
	g->Delete();
}
#endif

TH1D* Corr2Analysis::log(TH1D*h){
	TH1D *h_log=(TH1D*)h->Clone( Form("%s_log",h->GetName()));
	for(int i=1;i<=h_log->GetNbinsX() ;++i)
		{
		double y= h->GetBinContent(i);
		if(i>0) h_log->SetBinContent(i,TMath::Log(y) );
		}
	return h_log;
}
