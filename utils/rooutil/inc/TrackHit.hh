#ifndef TrackHit_hh_
#define TrackHit_hh_

#include <functional>
#include "EventNtuple/inc/TrkStrawHitInfo.hh"

struct TrackHit {
  TrackHit() { }
  TrackHit(mu2e::TrkStrawHitInfo* reco) : reco(reco) { }

  // Pointers to the data
  mu2e::TrkStrawHitInfo* reco = nullptr;
};

typedef std::function<bool(const TrackHit&)> TrackHitCut;
typedef std::vector<TrackHit> TrackHits;

#endif
