//
// An example of how to create a flatter tree if you want to do an unbinned lieklihood fit
// This uses cut functions defined in common_cuts.hh
//

#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

#include "TH1F.h"

void CreateNtuple(std::string filename) {

  // Set up RooUtil
  RooUtil util(filename);

  // Create an output file
  TFile* outfile = new TFile("example_ntuple.root", "RECREATE");
  util.CreateOutputEventNtuple(outfile);
  //  util.PrepareTrackTree(tree);

  // Loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    if (i_event % 2 == 0) {
      continue;
    }

    const auto& event = util.GetEvent(i_event);
    util.FillOutputEventNtuple();
  }

  outfile->Write();
  outfile->Close();
}
