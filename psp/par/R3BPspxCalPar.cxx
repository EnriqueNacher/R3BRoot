/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               R3BPspxCalPar source file                   -----
// -----                 Created 16/05/12  by I.Syndikus               -----
// -------------------------------------------------------------------------

#include "R3BPspxCalPar.h"

#include "FairParamList.h"
#include "FairDetParIo.h"
#include "FairParIo.h"
#include "FairLogger.h"
#include "TString.h"
#include "TMath.h"


// -----   Standard constructor   ------------------------------------------
R3BPspxCalPar::R3BPspxCalPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name, title, context),
    pspxcalpargain(-1),
    pspxcalparstrip(),
    pspxcalparstation(-1),
    pspxcalparorientation(-1)
{
  detName="Pspx";
  //  ftutdetdigipar= new TArrayF(10);
  //ftutdetdigipar= new TArrayF(10);
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
R3BPspxCalPar::~R3BPspxCalPar()
{
  clear();

}
// -------------------------------------------------------------------------


// -----   Public method clear   -------------------------------------------
void R3BPspxCalPar::clear()
{
  status = kFALSE;
  resetInputVersions();
}
// -------------------------------------------------------------------------

// -----   Public method printParams ---------------------------------------
void R3BPspxCalPar::printparams()
{

  LOG(INFO) <<"Print"<<FairLogger::endl;
  LOG(INFO) << "pspxcalparstation: " << pspxcalparstation 
	    << FairLogger::endl;
  Int_t size =  pspxcalparstrip.GetSize();
  LOG(INFO) <<"size: " << size << FairLogger::endl;
  LOG(INFO) << "Stationno.: No. of Strips, Orientation of strips" << FairLogger::endl;
  for ( Int_t i=0; i< size; i++) {
    LOG(INFO) << i <<" :" << pspxcalparstrip.GetAt(i) << ", " << pspxcalparorientation.GetAt(i) << FairLogger::endl;
  }
  
  size =  pspxcalpargain.GetSize();
  LOG(INFO) <<"size: " << size << FairLogger::endl;
  for ( Int_t i=0; i< size; i++) {
    LOG(INFO) << i <<" :" << pspxcalpargain.GetAt(i) << FairLogger::endl;
  }

}
// -------------------------------------------------------------------------

void R3BPspxCalPar::putParams(FairParamList* l)
{
  //   print();
  LOG(INFO) << "I am in R3BPspxCalPar::putParams " 
	    << FairLogger::endl;
  if (!l) { return; }
  l->add("R3BPspxCalStations", pspxcalparstation);
  l->add("R3BPspxCalStripsPerStation", pspxcalparstrip);
  l->add("R3BPspxCalOrientationOfStation", pspxcalparorientation);
  
  Int_t count_sectors = 0;
  for ( Int_t i=0; i< pspxcalparstation; i++) {
    count_sectors+=pspxcalparstrip[i];
  }
  Int_t array_size = (count_sectors * 2 + pspxcalparstation * 2); //????
  LOG(INFO) << "Array Size: " << array_size << FairLogger::endl;
  pspxcalpargain.Set(array_size);
  l->add("R3BPspxCalGainForStrips",pspxcalpargain);
  
}

//------------------------------------------------------

Bool_t R3BPspxCalPar::getParams(FairParamList* l)
{
  //print();

  LOG(INFO) << "I am in R3BPspxCalPar::getParams " 
	    << FairLogger::endl;

  if (!l) { return kFALSE; }
  if ( ! l->fill("R3BPspxCalStations", &pspxcalparstation) ) { return kFALSE; }
  pspxcalparstrip.Set(pspxcalparstation);
  pspxcalparorientation.Set(pspxcalparstation);

  if ( ! l->fill("R3BPspxCalStripsPerStation", &pspxcalparstrip) ) { return kFALSE; }
  if ( ! l->fill("R3BPspxCalOrientationOfStation", &pspxcalparorientation) ) { return kFALSE; }

  Int_t count_sectors = 0;
  for ( Int_t i=0; i< pspxcalparstation; i++) {
    count_sectors+=pspxcalparstrip[i];
  }
  LOG(INFO) << "Total number of strips: " << count_sectors
	    <<FairLogger::endl;

  Int_t array_size = (count_sectors * 2 + pspxcalparstation * 2); 
  LOG(INFO) << "Array Size: " << array_size << FairLogger::endl;
  pspxcalpargain.Set(array_size);
  if (!(l->fill("R3BPspxCalGainForStrips",&pspxcalpargain))) {
    LOG(WARNING) << "Could not initialize R3BPspxCalGainForStrips"
		 << FairLogger::endl;
    return kFALSE;
  }
  
  
  return kTRUE;
}



ClassImp(R3BPspxCalPar)