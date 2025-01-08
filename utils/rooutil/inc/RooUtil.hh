#ifndef RooUtil_hh_
#define RooUtil_hh_

#include <fstream>

#include "TFile.h"
#include "TTree.h"

#include "EventNtuple/utils/rooutil/inc/Event.hh"

class RooUtil {
public:
  RooUtil(std::string filename, std::string treename = "EventNtuple/ntuple") : debug(false) {
    ntuple = new TChain(treename.c_str());

    // Check if the given filename contains .root at the end
    std::string root_suffix = ".root";
    if (filename.compare(filename.size() - root_suffix.size(), root_suffix.size(), root_suffix) == 0) {
      ntuple->Add(filename.c_str());
    }
    else { //  assume its a file list
      std::ifstream filelist(filename);

      if (filelist.is_open()) {
        std::string line;
        while (std::getline(filelist, line)) {
          ntuple->Add(line.c_str());
        }
        filelist.close();
      } else {
        std::cout << "Error opening filelist." << std::endl;
      }
    }

    event = new Event(ntuple);
  }

  void Debug(bool dbg) { debug = dbg; }

  int GetNEvents() { return ntuple->GetEntries(); }

  Event& GetEvent(int i_event) {
    if (debug) { std::cout << "RooUtil::GetEvent(): Getting event " << i_event << std::endl; }
    ntuple->GetEntry(i_event);

    if (debug) { std::cout << "RooUtil::GetEvent(): Updating event " << i_event << std::endl; }
    event->Update(debug);

    if (debug) { std::cout << "RooUtil::GetEvent(): Returning event " << i_event << std::endl; }
    return *event;
  }

  void TurnOffBranch(const std::string& branchname) {
    ntuple->SetBranchStatus(branchname.c_str(), 0);
  }
  void TurnOnBranch(const std::string& branchname) {
    ntuple->SetBranchStatus(branchname.c_str(), 1);
  }
  void TurnOffBranches(const std::vector<std::string>& branchnames) {
    for (const auto& branchname : branchnames) {
      TurnOffBranch(branchname);
    }
  }
  void TurnOnBranches(const std::vector<std::string>& branchnames) {
    for (const auto& branchname : branchnames) {
      TurnOnBranch(branchname);
    }
  }
  void TurnOffAllBranches() {
    TurnOffBranch("*");
  }
  void TurnOnAllBranches() {
    TurnOnBranch("*");
  }

  void CreateOutputEventNtuple(TFile* outfile) {
    output_ntuple = new TTree("ntuple", "reduced ntuple");

    output_ntuple->Branch("evtinfo", event->evtinfo);
    output_ntuple->Branch("trk", event->trk);
  }

  void FillOutputEventNtuple() {
    output_ntuple->Fill();
  }

private:
  TChain* ntuple;
  Event* event; // holds all the variables for SetBranchAddress
  bool debug;

  TTree* output_ntuple; // for output
};

#endif
