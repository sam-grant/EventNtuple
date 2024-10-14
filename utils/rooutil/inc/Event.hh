#ifndef Event_hh_
#define Event_hh_

#include "EventNtuple/inc/EventInfo.hh"
#include "EventNtuple/inc/EventInfoMC.hh"

#include "EventNtuple/utils/rooutil/inc/Track.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple) {

    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
    ntuple->SetBranchAddress("trk", &this->trk);
    ntuple->SetBranchAddress("trksegs", &this->trksegs);

    // Check if the MC branches exist
    if (ntuple->GetBranch("evtinfomc")) {
      ntuple->SetBranchStatus("evtinfomc", 1);
      ntuple->SetBranchAddress("evtinfomc", &this->evtinfomc);
    }
  };

  void Update() {
    tracks.clear();

    for (int i_track = 0; i_track < nTracks(); ++i_track) {
      Track track(&(trk->at(i_track)), &(trksegs->at(i_track))); // passing the addresses of the underlying structs
      tracks.emplace_back(track);
    }
  }

  int nTracks() const { return trk->size(); }

  Tracks GetTracks() const { return tracks; }
  Tracks GetTracks(TrackCut cut) const {
    Tracks select_tracks;
    for (const auto& track : tracks) {
      if (cut(track)) {
        select_tracks.emplace_back(track);
      }
    }
    return select_tracks;
  }

  int CountTracks() const { return tracks.size(); }
  int CountTracks(TrackCut cut) const {
    Tracks select_tracks = GetTracks(cut);
    return select_tracks.size();
  }

  Tracks tracks;

  // Pointers to the data
  mu2e::EventInfo* evtinfo = nullptr;
  mu2e::EventInfoMC* evtinfomc = nullptr;

  std::vector<mu2e::TrkInfo>* trk = nullptr;
  std::vector<std::vector<mu2e::TrkSegInfo>>* trksegs = nullptr;
};

#endif
