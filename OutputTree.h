//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr  7 10:20:49 2014 by ROOT version 5.34/10
// from TTree OutputTree/Output tree
// found on file: TTHad_Tight_step2.root
//////////////////////////////////////////////////////////

#ifndef OutputTree_h
#define OutputTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class OutputTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           JetCount;
   Float_t         JetPT[120];
   Float_t         JetEta[120];
   Int_t           JetFlavor[120];
   Bool_t          JetTagged[120];
   Bool_t          JetTaggedPass1[120];
   Bool_t          JetTaggedPass2[120];
   Bool_t          JetTaggedPass2Up[120];
   Bool_t          JetTaggedPass2Down[120];
   Int_t           RunNumber;
   Long64_t        EventNumber;

   // List of branches
   TBranch        *b_JetCount;   //!
   TBranch        *b_JetPT;   //!
   TBranch        *b_JetEta;   //!
   TBranch        *b_JetFlavor;   //!
   TBranch        *b_JetTagged;   //!
   TBranch        *b_JetTaggedPass1;   //!
   TBranch        *b_JetTaggedPass2;   //!
   TBranch        *b_JetTaggedPass2Up;   //!
   TBranch        *b_JetTaggedPass2Down;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!

   OutputTree(TTree *tree=0);
   virtual ~OutputTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual std::map< double, std::vector<int> > Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef OutputTree_cxx
OutputTree::OutputTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/media/data2/Documents/cmorgoth/Data/TTbarBtagCorrected/BtagCodeNtuples/TTHad_Tight_step2.root");
     if (!f || !f->IsOpen()) {
       f = new TFile("/media/data2/Documents/cmorgoth/Data/TTbarBtagCorrected/BtagCodeNtuples/TTHad_Tight_step2.root");
     }
     f->GetObject("OutputTree",tree);
     
   }
   Init(tree);
}

OutputTree::~OutputTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t OutputTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t OutputTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void OutputTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("JetCount", &JetCount, &b_JetCount);
   fChain->SetBranchAddress("JetPT", JetPT, &b_JetPT);
   fChain->SetBranchAddress("JetEta", JetEta, &b_JetEta);
   fChain->SetBranchAddress("JetFlavor", JetFlavor, &b_JetFlavor);
   fChain->SetBranchAddress("JetTagged", JetTagged, &b_JetTagged);
   fChain->SetBranchAddress("JetTaggedPass1", JetTaggedPass1, &b_JetTaggedPass1);
   fChain->SetBranchAddress("JetTaggedPass2", JetTaggedPass2, &b_JetTaggedPass2);
   fChain->SetBranchAddress("JetTaggedPass2Up", JetTaggedPass2Up, &b_JetTaggedPass2Up);
   fChain->SetBranchAddress("JetTaggedPass2Down", JetTaggedPass2Down, &b_JetTaggedPass2Down);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   Notify();
}

Bool_t OutputTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void OutputTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t OutputTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef OutputTree_cxx
