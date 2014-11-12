#include "interface/Corr2Analysis.hpp"

#include "TMath.h"
#include "TGraph.h"

// solve equation mx+q == Ae^{-x/tau}
double Corr2Analysis::solve(double m , double q , double A ,double tau,double x,double epsilon)
{
        // metodo delle tangenti. Il piu' veloce.
        double y=A*TMath::Exp(-x/tau)-m*x-q;
        //cout<<" Iteration for solve: y="<< y <<" m="<<m<<" q="<<q<<" A="<<A<<" tau="<<tau<< " x="<<x <<" Exp="<<double(A*TMath::Exp(-x/tau)) << " line="<<m*x+q<<endl;
        if ( abs(y)< epsilon) return x;
        double m1=A*(-1./tau)*TMath::Exp(-x/tau) -m;
        double q1=y-m1*x;
        double x1= -q1/m1;
        //cout<<"Iteration for solve: x -> x1 "<<x1<< " m1="<<m1<<" q1="<<q1<<endl;
        return solve(m,q,A,tau,x1,epsilon);
}


void Corr2Analysis::ClearEvent()
{
	l->digi_charge_integrated_corr2->clear();
	l->digi_max_amplitude_corr2->clear();
	resetHistos(); // double called , but second time is just a check
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

}

void Corr2Analysis::Init(LoopAndFill *l1)
{
	BaseAnalysis::Init(l1);
	// check that these branches are input
	return;
}

void Corr2Analysis::Close(){
}

void Corr2Analysis::resetHistos(){
	for(unsigned int i=0;i<myhistos.size();++i)
		{
		myhistos[i]->Delete();
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
		float y=l->digiSampleValueSub[iSample];	
		UInt_t x=l->digiSampleIndex[iSample];
		myhistos[iCh]->SetBinContent(myhistos[iCh]->FindBin(x),y);
		}
	return ;
}


pair<double,double> Corr2Analysis::fit(TH1D*h)
{
// find max-ampl
        int iMax; float yMax,xMax;
        for(int i=1;i<=h->GetNbinsX();++i)
                {
                double y=h->GetBinContent(i);
                double x=h->GetBinCenter(i);
                if( i==1 || y>yMax) {yMax=y; iMax=i;xMax=x;}
                }
        // find 10% 50% points  --> will be used for fit ranges
        int i10_1,i10_2,i50_1,i50_2;
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
        line->SetRange(l1,l2);
        h->Fit(line,"WQR");
        h->Fit(line,"WQRM");
        q=line->GetParameter(0);
        m=line->GetParameter(1);
       double r1=h->GetBinCenter(i50_2);
        double r2=h->GetBinCenter(i10_2);
        TF1 *f=new TF1("expo","expo",r1,r2);
        f->SetParameter(1, -TMath::Log(2)/(i50_2-iMax) ); f ->SetParLimits(1, 0 ,-TMath::Log(2)/(i50_2-iMax)*10 );
        h->Fit(f,"WQR");
        h->Fit(f,"WQRM");
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
        h->Fit(f,"WQR");
        h->Fit(f,"WQRM");

        double x0= -q/m;

        double A=TMath::Exp(f->GetParameter(0));
        double tau=-1./f->GetParameter(1);
	
	TF1 *test=new TF1("expo_mod","[0]*(1.+[2]/x)*TMath::Exp(-x/[1])",r1 - (r1-xMax)/2.,TMath::Min(r2*2,1000.));
        test->SetParameter(0,A); test->SetParLimits(0,0,100*A);
        test->SetParameter(1,tau); test->SetParLimits(1,.2*tau,20*tau);
        test->SetParameter(2,0.0);
        h->Fit(test,"WQR");
        h->Fit(test,"WQRM");

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


        double x2=solve(m,q,A,tau);
        double area0=0.5*(x2-x0)*(x2-x0)*m + A*tau*TMath::Exp(-x2/tau);

        double A1=(m*x1+q)/TMath::Exp(-x1/tau);
        double area1=0.5*(x1-x0)*(x1-x0)*m + A1*tau*TMath::Exp(-x1/tau);

	pair<double,double> R(area0,area1);
	
	//delete everything you constructed
	delete line;
	delete f;
	delete test;
	return R;
}
