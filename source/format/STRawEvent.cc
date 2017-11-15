// =================================================
//  STRawEvent Class                          
//                                                  
//  Description:                                    
//    Container for a raw event data
//                                                  
//  Genie Jhang ( geniejhang@majimak.com )          
//  2013. 08. 16                                    
// =================================================

#include <iostream>
#include <iomanip>

#include "STRawEvent.hh"
#include "STPad.hh"

ClassImp(STRawEvent);

STRawEvent::STRawEvent()
:TNamed("STRawEvent", "Raw event container")
{
  fEventID = -2;
  fPadArray.reserve(108*112);

  fIsGood = kTRUE;
}

STRawEvent::STRawEvent(STRawEvent *object)
:TNamed("STRawEvent", "Raw event container")
{
  fEventID = object -> GetEventID();
  fPadArray = *(object -> GetPads());
  
  fIsGood = object -> IsGood();
}

STRawEvent::~STRawEvent()
{
}

void STRawEvent::Clear()
{
  fEventID = -2;
  fPadArray.clear();

  fIsGood = kTRUE;
}

void STRawEvent::PrintPads()
{
  for (Int_t iPad = 0; iPad < fPadArray.size(); iPad++) {
    std::cout << "Pad: " << std::setw(5) << iPad;
    std::cout << " (" << std::setw(3) << fPadArray[iPad].GetRow();
    std::cout << ", " << std::setw(3) << fPadArray[iPad].GetLayer() << ")";
    std::cout << std::endl;
  }
}

// setters
void STRawEvent::SetEventID(Int_t evtid) { fEventID = evtid; }
void STRawEvent::SetPad(STPad *pad)      { fPadArray.push_back(*pad); } 
void STRawEvent::SetIsGood(Bool_t value) { fIsGood = value; }
void STRawEvent::RemovePad(Int_t padNo) 
{
  if (!(padNo < GetNumPads()))
    return;

  fPadArray.erase(fPadArray.begin() + padNo);
}

void STRawEvent::RemovePad(Int_t row, Int_t layer) 
{
  for (Int_t iPad = 0; iPad < GetNumPads(); iPad++) {
    Int_t padRow = fPadArray[iPad].GetRow();
    Int_t padLayer = fPadArray[iPad].GetLayer();

    if (row == padRow && layer == padLayer)
      fPadArray.erase(fPadArray.begin() + iPad);
  }
}


// getters
             Int_t  STRawEvent::GetEventID()         { return fEventID; }
             Int_t  STRawEvent::GetNumPads()         { return fPadArray.size(); }
            Bool_t  STRawEvent::IsGood()             { return fIsGood; }
std::vector<STPad> *STRawEvent::GetPads()            { return &fPadArray; }
             STPad *STRawEvent::GetPad(Int_t padNo)  { return (padNo < GetNumPads() ? &fPadArray[padNo] : NULL); }

STPad *STRawEvent::GetPad(Int_t row, Int_t layer)
{
  for (Int_t iPad = 0; iPad < GetNumPads(); iPad++) {
    Int_t padRow = fPadArray[iPad].GetRow();
    Int_t padLayer = fPadArray[iPad].GetLayer();

    if (row == padRow && layer == padLayer)
      return &fPadArray[iPad];
  }

  return 0;
}

/*
void STRawEvent::SetHits(STEvent* event)
{
  Int_t numHits = event -> GetNumHits();
  for (Int_t iHit = 0; iHit < numHits; iHit++)
  {
    STHit *hit = event -> GetHit(iHit);
    GetPad(hit -> GetRow(), hit -> GetLayer()) -> AddHit(hit);
  }
}

void STRawEvent::SetHits(TClonesArray *array)
{
  Int_t numHits = array -> GetEntries();
  for (Int_t iHit = 0; iHit < numHits; iHit++)
  {
    STHit *hit = (STHit *) array -> At(iHit);
    GetPad(hit -> GetRow(), hit -> GetLayer()) -> AddHit(hit);
  }
}

void STRawEvent::ClearHits()
{
  for (Int_t iPad = 0; iPad < GetNumPads(); iPad++) 
    fPadArray.at(iPad).ClearHits();
}
*/
