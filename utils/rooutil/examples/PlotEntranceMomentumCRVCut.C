//
// An example of how to plot the momentum of electrons at the tracker entrance
// This uses cut functions defined in common_cuts.hh
//

#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

#include "TH1F.h"
#include "TCanvas.h"

void PlotEntranceMomentumCRVCut(std::string filename) {

  // Create the histogram you want to fill
  TH1F* hRecoMom = new TH1F("hRecoMom", "Reconstructed Momentum at Tracker Entrance", 50,95,110);
  TH1F* h_dt = new TH1F("h_dt", "Reconstructed Momentum at Tracker Entrance", 100,-500,500);

  // Set up RooUtil
  RooUtil util(filename);

  // Loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    // Get the next event
    const auto& event = util.GetEvent(i_event);

    // Get the e_minus tracks from the event
    const auto& e_minus_tracks = event.GetTracks(is_e_minus);

    const auto& crv_coincs = event.GetCrvCoincs();
    // Loop through the e_minus tracks
    for (const auto& track : e_minus_tracks) {

      // Get the track segments at the tracker entrance
      const auto& trk_ent_segments = track.GetSegments(tracker_entrance);

      // Loop through the tracker entrance track segments
      for (const auto& segment : trk_ent_segments) {

        for (const auto& crv_coinc : crv_coincs) {
          h_dt->Fill(segment.trkseg->time -  crv_coinc.reco->time);
          if (!track_crv_coincidence(segment, crv_coinc)) { // don't want track and crv hit to be coincident
            // Fill the histogram
            hRecoMom->Fill(segment.trkseg->mom.R());
            break;
          }
        }
      }
    }
  }

  // Draw the histogram
  TCanvas* c = new TCanvas("c", "c");
  c->Divide(2);
  c->cd(1);
  h_dt->Draw("HIST E");
  c->cd(2);
  hRecoMom->Draw("HIST E");
}
