//
// An example of how to plot the initial z-position of MCParticle muons
// This uses cut functions defined in common_cuts.hh
//

#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

#include "TH1F.h"

void PlotMCParticleMom(std::string filename) {

  // Create the histogram you want to fill
  TH1F* hCeMinusMom = new TH1F("hCeMinusMom", "", 150,95,110);
  TH1F* hDIOMom = new TH1F("hDIOMom", "", 150,95,110);

  // Set up RooUtil
  RooUtil util(filename);
  //  util.Debug(true);
  // Loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    // Get the next event
    const auto& event = util.GetEvent(i_event);

    // Get the e_minus tracks from the event
    const auto& e_minus_tracks = event.GetTracks(is_e_minus);

    // Loop through the e_minus tracks
    for (const auto& track : e_minus_tracks) {

      // Get the track segments at the tracker entrance and has an MC step
      const auto& ce_particles = track.GetMCParticles(is_CeMinusLeadingLog);
      // Loop through the tracker entrance track segments
      for (const auto& particle : ce_particles) {
        // Fill the histogram
        hCeMinusMom->Fill(particle.mcsim->mom.R());
      }

      // Get the track segments at the tracker entrance and has an MC step
      const auto& dio_particles = track.GetMCParticles(is_DIO);
      // Loop through the tracker entrance track segments
      for (const auto& particle : dio_particles) {
        // Fill the histogram
        hDIOMom->Fill(particle.mcsim->mom.R());
      }
    }
  }

  // Draw the histogram
  hDIOMom->SetLineColor(kBlue);
  hDIOMom->Draw("HIST E");
  hCeMinusMom->SetLineColor(kRed);
  hCeMinusMom->Draw("HIST E SAME");
}
