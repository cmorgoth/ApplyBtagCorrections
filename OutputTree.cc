#define OutputTree_cxx
#include "OutputTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

std::map< double, std::vector<int> > OutputTree::Loop(){
  
  //if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  std::map< double, std::vector<int> > evt_btag_map;//Event number is the key and an array contains the bBtag Information
  int nBtagCorrA[3] = {0,0,0};
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    std::vector<int> nBtagC;
    
    for(int i = 0; i < 50; i++){
      
      if(JetPT[i] < 40 || JetEta[i] < -2.4 || JetEta[i] > 2.4)continue;
      
      if(JetTaggedPass2[i] == true)nBtagCorrA[0]++;
      if(JetTaggedPass2Up[i] == true)nBtagCorrA[1]++;
      if(JetTaggedPass2Down[i] == true)nBtagCorrA[2]++;
    }
    
    for(int j = 0; j < 50; j++){
      JetTaggedPass2[j] = false;
      JetTaggedPass2Up[j] = false;
      JetTaggedPass2Down[j] = false;
    }
    
    for(int k = 0; k < 3; k++){
      nBtagC.push_back( nBtagCorrA[k] );
      nBtagCorrA[k] = 0;
    }
    
    if(nBtagC.size() < 3)std::cout << "what!!!" << jentry << std::endl;
    evt_btag_map[EventNumber] = nBtagC;
    
  }
  
  return evt_btag_map;
  
}
