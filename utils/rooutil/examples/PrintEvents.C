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

    // trkmc branch
    if (has_mc) {
      for (const auto& trkmc : *(event.trkmc)) {
        std::cout << "trkmc: " << trkmc.valid << "," << trkmc.nhits << "," << trkmc.nactive << "," << trkmc.t0 << std::endl;
      }
    }

    // trksegs branch
    for (const auto& trksegs : *(event.trksegs)) {
      std::cout << "New Track!" << std::endl;
      for (const auto& trkseg : trksegs) {
        std::cout << "trksegs: time = " << trkseg.time << " ns, p_mag = " << trkseg.mom.R() << " MeV/c, sid = " << trkseg.sid << ", p_z = " << trkseg.mom.z() << " MeV/c, z = " << trkseg.pos.z() << " mm" << std::endl;
      }
    }
    if (has_mc) {
      for (const auto& trksegsmc : *(event.trksegsmc)) {
        std::cout << "New Track!" << std::endl;
        for (const auto& trksegmc : trksegsmc) {
          std::cout << "trksegsmc: t = " << trksegmc.time << " ns, p_mag = " << trksegmc.mom.R() << " MeV/c, sid = " << trksegmc.sid << ", p_z = " << trksegmc.mom.z() << " MeV/c, z = " << trksegmc.pos.z() << " mm" <<std::endl;
        }
      }
    }

    // trkcalohit branch
    for (const auto& trkcalohit : *(event.trkcalohit)) {
      std::cout << "trkcalohit: " << trkcalohit.active << "," << trkcalohit.mom.R() << "," << trkcalohit.edep << "," << trkcalohit.edeperr << std::endl;
    }

    // trkcalohitmc branch
    if (has_mc) {
      for (const auto& trkcalohitmc : *(event.trkcalohitmc)) {
        std::cout << "trkcalohitmc: " << trkcalohitmc.nsim << "," << trkcalohitmc.etot << "," << trkcalohitmc.prel.relationship() << std::endl;
      }
    }


    // crvcoincs branch
    for (const auto& crvcoinc : *(event.crvcoincs)) {
      std::cout << "crvcoinc: " << crvcoinc.sectorType << "," << crvcoinc.PEs << "," << crvcoinc.angle << std::endl;
      for (const auto& layer_PE : crvcoinc.PEsPerLayer) {
        std::cout << "crvcoinc layer PE: " << layer_PE << std::endl;
      }
    }

    // crvcoincsmc branch
    if (has_mc) {
      for (const auto& crvcoincmc : *(event.crvcoincsmc)) {
        std::cout << "crvcoincmc: " << crvcoincmc.valid << "," << crvcoincmc.pdgId << "," << crvcoincmc.depositedEnergy << std::endl;
      }
    }

    if (has_mc) {
      for (const auto& trkmcsim : *(event.trkmcsim)) {
        std::cout << "New Track!" << std::endl;
        for (const auto& sim : trkmcsim) {
          std::cout << "trkmcsim: valid = " << sim.valid << ", nhits = " << sim.nhits << ", pdg = " << sim.pdg << ", p = " << sim.mom.R() << ", prirel = " << (int)sim.prirel.relationship() << ", trkrel = " << (int)sim.trkrel.relationship() << std::endl;
        }
      }
    }

    // trkqual branch
    for (const auto& trkqual : *(event.trkqual)) {
      std::cout << "trkqual: " << trkqual.valid << ", " << trkqual.result << std::endl;
    }

    // trksegpars_lh
    if (event.trksegpars_lh != nullptr) { // might not have this branch
      for (const auto& track : *(event.trksegpars_lh)) {
        std::cout << "New Track!" << std::endl;
        for (const auto& trksegpars : track) {
          std::cout << "trksegpars_lh: " << trksegpars.maxr << ", " << trksegpars.t0 << ", " << trksegpars.t0err << std::endl;
        }
      }
    }
  }
}
