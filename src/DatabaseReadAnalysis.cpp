#include "interface/DatabaseReadAnalysis.hpp"
#include <assert.h>


void DatabaseReadAnalysis::AnalyzeEvent()
{
// do caching correctly
  static int lastRun=-1;

  if ( l->runNumber == lastRun) loaded=true;
  else loaded = false;


  if (!loaded) {
    mydb->LoadRun(l->runNumber);
    //loaded = true;
  }

  lastRun=l->runNumber;

  l->TableX = mydb->Get("table_horizontal_position").Atof();
  l->TableY = mydb->Get("table_vertical_position").Atof();
  l->CeF3HV = mydb->Get("cef3_hv").Atof();
  l->BGOHV = mydb->Get("bgo_hv").Atof();
  l->BeamEnergy = mydb->Get("beam_energy").Atof();
  l->BeamTilt = mydb->Get("beam_horizontal_tilt").Atof();
  l->IsPhysics = (mydb->Get("run_type_description")==TString("PHYSICS")) ? 1 : 0;

  return;
}

void DatabaseReadAnalysis::Init(LoopAndFill *l1)
{
	cout<<"[DatabaseReadAnalysis]::[Init]"<<endl;
	BaseAnalysis::Init(l1);

	mydb = new RunDBInterface(databasename,tablename,"","");
	loaded = false;

	cout<<"[DatabaseReadAnalysis]::[Init]::Done"<<endl;
	return ;
}



