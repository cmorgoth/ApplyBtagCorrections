#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"
#include "OutputTree.h"

int main(){

  gROOT->Reset();
  //std::cout.precision(17);
  
  //Original File
  TFile* f = new TFile("/media/data/cmorgoth/Data/DMData/TTJets/TTJetsHad_pu_mu_tot.root");
  TTree* t = (TTree*)f->Get("outTree");
  TTree* eff = (TTree*)f->Get("effTree");
  
  //Branches to be read from the Original Tree
  double evNum;
  t->SetBranchAddress("evNum", &evNum);
  
  OutputTree* bt = new OutputTree();
  
  //Number of entries for each tree
  //int Nentries = t->GetEntries();
  long long Nentries = t->GetEntriesFast();
  //Output Tree, with corrections applied
  TFile* nf = new TFile("/media/data2/Documents/cmorgoth/Data/TTbarBtagCorrected/TightCorrectedFinalNtuples/TTJetsHad_pu_mu_TightCorr.root"
			,"RECREATE");
  TTree* nt = t->CloneTree(0);
  TTree* neff = eff->CloneTree(0);
  
  //Branches to be added
  int nBtagCorr, nBtagCorrUp, nBtagCorrDown;
  nt->Branch("nBtagTCorr", &nBtagCorr, "nBtagTCorr/I");
  nt->Branch("nBtagTCorrUp", &nBtagCorrUp, "nBtagTCorrUp/I");
  nt->Branch("nBtagTCorrDown", &nBtagCorrDown, "nBtagTCorrDown/I");
  
  
  std::map< double, std::vector<int> > evt_btag_map;//Event number is the key and an array contains the bBtag Information
  evt_btag_map = bt->Loop();
  std::cout << "========Nentries:  " << Nentries << "===========" <<std::endl;
  for(long long l = 0; l < Nentries; l++){
    t->GetEntry(l);
    if(l % 10000 == 0)std::cout << "entry: " << l << std::endl;
    //if(evt_btag_map[(int)evNum].at(0)==0){
    //std::cout << evt_btag_map[(int)evNum].at(0) << "\t" << evt_btag_map[(int)evNum].at(0) << "\t"<< evt_btag_map[(int)evNum].at(0) << std::endl;
    //}
    
    if(evt_btag_map[(int)evNum].size() < 3){
      std::cout << "small vector " << l << std::endl;
    }else{
      nBtagCorr = evt_btag_map[(int)evNum].at(0);
      nBtagCorrUp = evt_btag_map[(int)evNum].at(1);
      nBtagCorrDown = evt_btag_map[(int)evNum].at(2);
    }
    nt->Fill();
  }
  
  for(int i = 0; i < eff->GetEntries(); i++){
    eff->GetEntry(i);
    neff->Fill();
  }
  
  nt->Write();
  neff->Write();
  return 0;
  
}
