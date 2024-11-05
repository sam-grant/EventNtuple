#ifndef Event_hh_
#define Event_hh_

#include "EventNtuple/inc/EventInfo.hh"
#include "EventNtuple/inc/EventInfoMC.hh"
#include "EventNtuple/inc/TrkInfoMC.hh"
#include "EventNtuple/inc/TrkCaloHitInfo.hh"

#include "EventNtuple/inc/CrvHitInfoReco.hh"

#include "EventNtuple/utils/rooutil/inc/Track.hh"
#include "EventNtuple/utils/rooutil/inc/CrvCoinc.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple) {

    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);

    ntuple->SetBranchAddress("trk", &this->trk);
    ntuple->SetBranchAddress("trksegs", &this->trksegs);
    ntuple->SetBranchAddress("trkcalohit", &this->trkcalohit);

    ntuple->SetBranchAddress("crvcoincs", &this->crvcoincs);

    // Check if the MC branches exist
    if (ntuple->GetBranch("evtinfomc")) {
      ntuple->SetBranchAddress("evtinfomc", &this->evtinfomc);
    }
    if (ntuple->GetBranch("trkmc")) {
      ntuple->SetBranchAddress("trkmc", &this->trkmc);
    }
    if (ntuple->GetBranch("trksegsmc")) {
      ntuple->SetBranchAddress("trksegsmc", &this->trksegsmc);
    }
  };

  void Update() {
    tracks.clear();
    for (int i_track = 0; i_track < nTracks(); ++i_track) {
      Track track(&(trk->at(i_track)), &(trksegs->at(i_track)), &(trkcalohit->at(i_track))); // passing the addresses of the underlying structs
      if (trkmc != nullptr) {
        track.trkmc = &(trkmc->at(i_track));
      }
      if (trksegsmc != nullptr) {
        track.trksegsmc = &(trksegsmc->at(i_track));
      }
      track.Update();
      tracks.emplace_back(track);
    }

    crv_coincs.clear();
    for (int i_crv_coinc = 0; i_crv_coinc < nCrvCoincs(); ++i_crv_coinc) {
      CrvCoinc crv_coinc(&(crvcoincs->at(i_crv_coinc)));
      crv_coincs.emplace_back(crv_coinc);
    }
  }

  int nTracks() const { return trk->size(); }
  int nCrvCoincs() const { return crvcoincs->size(); }

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

  CrvCoincs GetCrvCoincs() const { return crv_coincs; }
  CrvCoincs GetCrvCoincs(CrvCoincCut cut) const {
    CrvCoincs select_crv_coincs;
    for (const auto& crv_coinc : crv_coincs) {
      if (cut(crv_coinc)) {
        select_crv_coincs.emplace_back(crv_coinc);
      }
    }
    return select_crv_coincs;
  }

  int CountTracks() const { return tracks.size(); }
  int CountTracks(TrackCut cut) const {
    Tracks select_tracks = GetTracks(cut);
    return select_tracks.size();
  }

  int CountCrvCoincs() const { return crv_coincs.size(); }
  int CountCrvCoincs(CrvCoincCut cut) const {
    CrvCoincs select_crv_coincs = GetCrvCoincs(cut);
    return select_crv_coincs.size();
  }

  Tracks tracks;
  CrvCoincs crv_coincs;

  // Pointers to the data
  mu2e::EventInfo* evtinfo = nullptr;
  mu2e::EventInfoMC* evtinfomc = nullptr;

  std::vector<mu2e::TrkInfo>* trk = nullptr;
  std::vector<mu2e::TrkInfoMC>* trkmc = nullptr;
  std::vector<mu2e::TrkCaloHitInfo>* trkcalohit = nullptr;
  std::vector<std::vector<mu2e::TrkSegInfo>>* trksegs = nullptr;
  std::vector<std::vector<mu2e::SurfaceStepInfo>>* trksegsmc = nullptr;

  std::vector<mu2e::CrvHitInfoReco>* crvcoincs = nullptr;
};

#endif
