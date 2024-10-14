//
// This macro prints the a couple of leaves from each branch
// to test direct access to the branches via RooUtil's Event class
//
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

#include <iostream>

void PrintEvents(std::string filename, bool has_mc = false) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;

  // Only print one event
  for (int i_event = 0; i_event < 1; ++i_event) {
    const auto& event = util.GetEvent(i_event);

    // evtinfo branch
    std::cout << "evtinfo: "<< event.evtinfo->run << "," << event.evtinfo->subrun << "," << event.evtinfo->event << "," << event.evtinfo->nprotons << "," << event.evtinfo->pbtime << "," << event.evtinfo->pbterr << std::endl;

    // evtinfomc branch
    if (has_mc) {
      std::cout << "evtinfomc: " << event.evtinfomc->nprotons << "," << event.evtinfomc->pbtime << std::endl;
    }

    // trk branch
    for (const auto& trk : *(event.trk)) {
      std::cout << "trk: " << trk.status << "," << trk.nhits << "," << trk.nactive << "," << trk.avgedep << std::endl;
    }

    // trksegs branch
    for (const auto& trksegs : *(event.trksegs)) {
      for (const auto& trkseg : trksegs) {
        std::cout << "trksegs: " << trkseg.mom.R() << "," << trkseg.sid << "," << trkseg.sindex << std::endl;
      }
    }
  }
}
