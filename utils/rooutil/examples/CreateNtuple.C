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
  for (int i_event = 0; i_event < 10; ++i_event){//util.GetNEvents(); ++i_event) {
    //    if (i_event % 2 == 0) {
    //      continue;
    //    }

    auto& event = util.GetEvent(i_event);

    std::cout << "AE: Total N Tracks = " << event.CountTracks() << std::endl;;
    std::cout << "AE: Total is_e_minus tracks = " << event.CountTracks(is_e_minus) << std::endl;
    std::cout << "AE: Total N Tracks again = " << event.CountTracks() << std::endl;;
    std::cout << "AE: Select tracks" << std::endl;
    event.SelectTracks(is_e_minus);
    std::cout << "AE: Count all tracks aagain " << event.CountTracks() << std::endl;
    if (event.CountTracks() == 1) {
      util.FillOutputEventNtuple();
    }

    //  std::cout << "Reset and count again" << std::endl;
    // event = util.GetEvent(i_event);
    // std::cout << "N tracks = " << event.CountTracks() << std::endl;
    // std::cout << std::endl;
  }

  outfile->Write();
  outfile->Close();
}
