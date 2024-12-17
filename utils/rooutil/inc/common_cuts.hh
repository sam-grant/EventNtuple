//
// This file contains common cut functions that you might want to use.
// You can use these in your own functions too
//

#ifndef common_cuts_hh_
#define common_cuts_hh_

#include "Offline/DataProducts/inc/PDGCode.hh"
#include "Offline/MCDataProducts/inc/ProcessCode.hh"
#include "Offline/MCDataProducts/inc/GenId.hh"
#include "Offline/MCDataProducts/inc/MCRelationship.hh"

#include "EventNtuple/utils/rooutil/inc/Track.hh"
#include "EventNtuple/utils/rooutil/inc/TrackSegment.hh"
#include "EventNtuple/utils/rooutil/inc/CrvCoinc.hh"

//+ Track Segment Cuts - Directions
bool is_downstream(const TrackSegment& segment) { // track fit segment is going in +z direction
  // the sign of p_z tells us whether this segment is going upstream or downstream
  if (segment.trkseg->mom.z() > 0) {
      return true;
  }
  else { return false; }
}

bool is_upstream(const TrackSegment& segment) { // track fit segment is going in -z direction
  // the sign of p_z tells us whether this segment is going upstream or downstream
  if (segment.trkseg->mom.z() < 0) {
    return true;
  }
  else { return false; }
}


//+ Track Segment Cuts - Locations
bool tracker_entrance(const TrackSegment& segment) { // track fit segment is at the tracker entrance
  if (segment.trkseg != nullptr) {
    if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Front) { return true; }
    else { return false; }
  }
  if (segment.trksegmc != nullptr) {
    if (segment.trksegmc->sid==mu2e::SurfaceIdDetail::TT_Front) { return true; }
    else { return false; }
  }
  else { return false; }
}

bool tracker_middle(const TrackSegment& segment) {  // track fit segment is at the middle of the tracker
  if (segment.trkseg != nullptr) {
    if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Mid) { return true; }
    else { return false; }
  }
  if (segment.trksegmc != nullptr) {
    if (segment.trksegmc->sid==mu2e::SurfaceIdDetail::TT_Mid) { return true; }
    else { return false; }
  }
  else { return false; }
}

bool tracker_exit(const TrackSegment& segment) { // track fit segment is at the tracker exit
  if (segment.trkseg != nullptr) {
    if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Back) { return true; }
    else { return false; }
  }
  if (segment.trksegmc != nullptr) {
    if (segment.trksegmc->sid==mu2e::SurfaceIdDetail::TT_Back) { return true; }
    else { return false; }
  }
  else { return false; }
}

bool stopping_target_foils(const TrackSegment& segment) { // track fit segment is in the stopping target
  if (segment.trkseg != nullptr) {
    if (segment.trkseg->sid==mu2e::SurfaceIdDetail::ST_Foils) { return true; }
    else { return false; }
  }
  else if (segment.trksegmc != nullptr) {
    if (segment.trksegmc->sid==mu2e::SurfaceIdDetail::ST_Foils) { return true; }
    else { return false; }
  }
  else { return false; }
}
//+ Track Segment Cuts - Other
bool has_mc_step(const TrackSegment& segment) { // track fit segment has an MC-truth SurfaceStep
  if (segment.trksegmc != nullptr) { return true; }
  else { return false; }
}
bool has_reco_step(const TrackSegment& segment) { // track fit segment has an reco SurfaceStep
  if (segment.trkseg != nullptr) { return true; }
  else { return false; }
}


//+ Track Cuts - Particle Types
bool is_particle(const Track& track, mu2e::PDGCode::type particle) { // track fit used particle hypothesis
  if (track.trk->pdg == particle) { return true; }
  else { return false; }
}

bool is_e_minus(const Track& track) { // track fit used e-minus hypothesis
  return is_particle(track, mu2e::PDGCode::e_minus);
}

bool is_e_plus(const Track& track) { // track fit used e-plus hypothesis
  return is_particle(track, mu2e::PDGCode::e_plus);
}

bool is_mu_minus(const Track& track) { // track fit used mu-minus hypothesis
  return is_particle(track, mu2e::PDGCode::mu_minus);
}

bool is_mu_plus(const Track& track) { // track fit used mu-plus hypothesis
  return is_particle(track, mu2e::PDGCode::mu_plus);
}

//+ Track Cuts - Other
bool is_reflected(const Track& track) { // track is refelected (i.e. has both an upstream and downstream fit segment at the tracker entrance)
  bool have_upstream = false;
  bool have_downstream = false;
  for (const auto& segment : track.segments) {
    if (tracker_entrance(segment)) {
      if (is_upstream(segment)) {
        have_upstream = true;
      }
      if (is_downstream(segment)) {
        have_downstream = true;
      }
    }
  }
  if (have_upstream && have_downstream) {
    return true;
  }
  else {
    return false;
  }
}

bool passes_trkqual(const Track& track, double cut_val) { // true if trkqual > cut_val
  if (track.trkqual->result > cut_val) { return true; }
  else { return false; }
}

//+ CrvCoinc Cuts
bool three_of_four_coinc(const CrvCoinc& crv_coinc) { // CRV coincidence has exactly three layers hit
  if (crv_coinc.reco->nLayers == 3) { return true; }
  else { return false; }
}

//+ Combined Track & CrvCoinc Cuts
bool track_crv_coincidence(const TrackSegment& segment, const CrvCoinc& crv_coinc) { // time difference between track segment and crv_coinc is less than 250 ns
  if ( segment.trkseg->time - crv_coinc.reco->time > 200 && segment.trkseg->time - crv_coinc.reco->time < 450) { return true; }
  else { return false; }
}

//+ MCParticle Cuts - Particle Types
bool is_particle(const MCParticle& particle, mu2e::PDGCode::type pdg) { // MCParticle has pdg
  if (particle.mcsim->pdg == pdg) { return true; }
  else { return false; }
}
bool is_muon(const MCParticle& sim) { // true if the MCParticle is a muon
  return is_particle(sim, mu2e::PDGCode::mu_minus);
}

//+ MCParticle Cuts - Start Process Code
bool start_process(const MCParticle& particle, mu2e::ProcessCode::enum_type proc) { // MCParticle has this creation code
  if (particle.mcsim->startCode == proc) { return true; }
  else { return false; }
}
bool is_CeMinusEndpoint(const MCParticle& particle) { // true of the MCParticle is CeMinusEndpoint
  return start_process(particle, mu2e::ProcessCode::mu2eCeMinusEndpoint);
}
bool is_CeMinusLeadingLog(const MCParticle& particle) { // true of the MCParticle is CeMinusLeadingLog
  return start_process(particle, mu2e::ProcessCode::mu2eCeMinusLeadingLog);
}
bool is_DIO(const MCParticle& particle) { // true of the MCParticle is DIO or mu2eDIOLeadingLof
  return (start_process(particle, mu2e::ProcessCode::mu2eMuonDecayAtRest) || start_process(particle, mu2e::ProcessCode::DIO));
}

//+ MCParticle Cuts - Stop Process Code
bool end_process(const MCParticle& particle, mu2e::ProcessCode::enum_type proc) { // MCParticle has this stop code
  if (particle.mcsim->stopCode == proc) { return true; }
  else { return false; }
}

//+ MCParticle Cuts - Generator ID
bool end_process(const MCParticle& particle, mu2e::GenId::enum_type genid) { // MCParticle has this generator ID
  if (particle.mcsim->gen == genid) { return true; }
  else { return false; }
}

//+ MCParticle Cuts - Genealogy
bool has_track_relationship(const MCParticle& particle, mu2e::MCRelationship::relation rel) { // MCParticle has this relationship to track primary
  if (particle.mcsim->trkrel == rel) { return true; }
  else { return false; }
}
bool is_track_parent(const MCParticle& particle) { // MCParticle is the parent of the track
  return has_track_relationship(particle, mu2e::MCRelationship::mother);
}
bool has_primary_relationship(const MCParticle& particle, mu2e::MCRelationship::relation rel) { // MCParticle has this relationship to event primary
  if (particle.mcsim->prirel == rel) { return true; }
  else { return false; }
}

//+ MCParticle Cuts - Other
bool made_track_hit(const MCParticle& particle) { // MCParticle made a hit in the tracker
  if (particle.mcsim->nhits > 0) { return true; }
  else { return false; }
}

#endif
