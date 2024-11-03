#ifndef Track_hh_
#define Track_hh_

#include <functional>
#include "EventNtuple/inc/TrkInfo.hh"
#include "EventNtuple/inc/TrkSegInfo.hh"
#include "EventNtuple/inc/TrkCaloHitInfo.hh"

#include "EventNtuple/utils/rooutil/inc/TrackSegment.hh"

struct Track {
  Track(mu2e::TrkInfo* trk, std::vector<mu2e::TrkSegInfo>* trksegs, mu2e::TrkCaloHitInfo* trkcalohit)
    : trk(trk), trksegs(trksegs), trkcalohit(trkcalohit) {

    // Create the underlying track segments
    for (int i_segment = 0; i_segment < nSegments(); ++i_segment) {
      TrackSegment segment(&(trksegs->at(i_segment))); // passing the addresses of the underlying structs
      segments.emplace_back(segment);
    }

    // Time order the segments
    std::sort(segments.begin(), segments.end(), TrackSegment::earliest);
  }

  void Update() {
    for (auto& segment : segments) {
      if (trksegsmc != nullptr) { // if we have MC information
        // search for corresponding SurfaceStepInfo (it will have the same sid and sindex)
        // also, trksegs and trksegms may not be the same length...
        for (size_t i_segment_mc = 0; i_segment_mc < trksegsmc->size(); ++i_segment_mc) {
          if (segment.trkseg->sid == trksegsmc->at(i_segment_mc).sid
              && segment.trkseg->sindex == trksegsmc->at(i_segment_mc).sindex) {

            segment.trksegmc = &(trksegsmc->at(i_segment_mc));
          }
        }
      }
    }
  }

  int nSegments() const { return trksegs->size(); }

  TrackSegments GetSegments() const { return segments; }
  TrackSegments GetSegments(TrackSegmentCut cut) const {
    TrackSegments select_segments;
    for (const auto& segment : segments) {
      if (cut(segment)) {
        select_segments.emplace_back(segment);
      }
    }
    return select_segments;
  }

  TrackSegments segments;

  // Pointers to the data
  mu2e::TrkInfo* trk = nullptr;
  mu2e::TrkInfoMC* trkmc = nullptr;
  std::vector<mu2e::TrkSegInfo>* trksegs = nullptr;
  std::vector<mu2e::SurfaceStepInfo>* trksegsmc = nullptr;
  mu2e::TrkCaloHitInfo* trkcalohit = nullptr;
};

typedef std::function<bool(const Track&)> TrackCut;
typedef std::vector<Track> Tracks;

#endif
