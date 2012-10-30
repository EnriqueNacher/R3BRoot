// -------------------------------------------------------------------------
// -----                  R3BCaloCrystalHit header file                -----
// -----               Created 08/07/10  by H. Alvarez Pol             -----
// -----	     Last modification 28/05/12 by P.Cabanelas         -----
// -------------------------------------------------------------------------

/**  R3BCaloCrystalHit.h
 **  A calorimeter crystal hit is the representation of the 
 **  information obtained from each crystal in the calorimeter.
 **/

#ifndef R3BCALOCRYSTALHIT_H
#define R3BCALOCRYSTALHIT_H

#include "TObject.h"
#include "FairMultiLinkedData.h"

class R3BCaloCrystalHit : public FairMultiLinkedData 
{
public:

  /** Default constructor **/
  R3BCaloCrystalHit();

  /** Constructor with arguments
   *@param fCrystalId   Crystal unique identifier
   *@param fEnergy      Total energy deposited on the crystal [GeV]
   *@param fTime        Time since event start [ns]
   **/
  R3BCaloCrystalHit(Int_t ident, Double_t energy, Double_t time);

  /** Copy constructor **/
  R3BCaloCrystalHit(const R3BCaloCrystalHit& hit) { *this = hit; };

  /** Destructor **/
  virtual ~R3BCaloCrystalHit();

  /** Accessors **/
  Int_t    GetCrystalId()     const { return fCrystalId; }
  Double_t GetEnergy()        const { return fEnergy; }
  Double_t GetTime()          const { return fTime; }
	
  Int_t    GetCrystalType()   const { return 0; }   //Backwards compatibility: not crashing macros
  Int_t    GetCrystalCopy()   const { return 0; }   //Backwards compatibility: not crashing macros

  /** Modifiers **/
  void SetCrystalId(Int_t ident)            { fCrystalId = ident; }
  void SetEnergy(Double32_t energy){fEnergy = energy;}
  void SetTime(Double32_t time){fTime = time;}

  /** Output to screen **/
  virtual void Print(const Option_t* opt) const;

protected:

  Double32_t fEnergy;    //total energy in the crystal
  Double32_t fTime;      //time of the interaction
  Int_t fCrystalId;      //crystal unique identifier

  ClassDef(R3BCaloCrystalHit,1)

};

#endif
