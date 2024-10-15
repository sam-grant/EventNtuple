//
// create_val_file_rooutil.C
// -- this macro creates a histogram for every leaf in the EventNtuple using the RooUtil interface
//

#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
// TODO: can add common_cuts.hh here

#include "TH1F.h"

void create_val_file_rooutil(std::string filename, std::string outfilename) {

  RooUtil util(filename);

  TFile* file = new TFile(outfilename.c_str(), "RECREATE");

  TH1F* h_evtinfo_event = new TH1F("h_evtinfo_event", "", 100,0,1000);
  TH1F* h_evtinfo_subrun = new TH1F("h_evtinfo_subrun", "", 100,0,1000);
  TH1F* h_evtinfo_run = new TH1F("h_evtinfo_run", "", 100,0,1000);
  TH1F* h_evtinfo_nprotons = new TH1F("h_evtinfo_nprotons", "", 100,0,1000);
  TH1F* h_evtinfo_pbtime = new TH1F("h_evtinfo_pbtime", "", 100,-500,500);
  TH1F* h_evtinfo_pbterr = new TH1F("h_evtinfo_pbterr", "", 100,-1,1);

  TH1F* h_evtinfomc_nprotons = new TH1F("h_evtinfomc_nprotons", "", 100,0,1000);
  TH1F* h_evtinfomc_pbtime = new TH1F("h_evtinfomc_pbtime", "", 100,-500,500);

  TH1F* h_trk_status = new TH1F("h_trk_status", "", 100,0,100);
  TH1F* h_trk_goodfit = new TH1F("h_trk_goodfit", "", 100,0,100);
  TH1F* h_trk_seedalg = new TH1F("h_trk_seedalg", "", 100,0,100);
  TH1F* h_trk_fitalg = new TH1F("h_trk_fitalg", "", 100,0,100);
  TH1F* h_trk_pdg = new TH1F("h_trk_pdg", "", 100,0,100);
  TH1F* h_trk_nhits = new TH1F("h_trk_nhits", "", 100,0,100);
  TH1F* h_trk_ndof = new TH1F("h_trk_ndof", "", 100,0,100);
  TH1F* h_trk_nactive = new TH1F("h_trk_nactive", "", 100,0,100);
  TH1F* h_trk_ndouble = new TH1F("h_trk_ndouble", "", 100,0,100);
  TH1F* h_trk_ndactive = new TH1F("h_trk_ndactive", "", 100,0,100);
  TH1F* h_trk_nplanes = new TH1F("h_trk_nplanes", "", 100,0,100);
  TH1F* h_trk_planespan = new TH1F("h_trk_planespan", "", 100,0,100);
  TH1F* h_trk_nnullambig = new TH1F("h_trk_nnullambig", "", 100,0,100);
  TH1F* h_trk_nmat = new TH1F("h_trk_nmat", "", 100,0,100);
  TH1F* h_trk_nmatactive = new TH1F("h_trk_nmatactive", "", 100,0,100);
  TH1F* h_trk_nesel = new TH1F("h_trk_nesel", "", 100,0,100);
  TH1F* h_trk_nrsel = new TH1F("h_trk_nrsel", "", 100,0,100);
  TH1F* h_trk_ntsel = new TH1F("h_trk_ntsel", "", 100,0,100);
  TH1F* h_trk_nbkg = new TH1F("h_trk_nbkg", "", 100,0,100);
  TH1F* h_trk_nsel = new TH1F("h_trk_nsel", "", 100,0,100);
  TH1F* h_trk_nseg = new TH1F("h_trk_nseg", "", 100,0,100);
  TH1F* h_trk_nipaup = new TH1F("h_trk_nipaup", "", 100,0,100);
  TH1F* h_trk_nipadown = new TH1F("h_trk_nipadown", "", 100,0,100);
  TH1F* h_trk_nstup = new TH1F("h_trk_nstup", "", 100,0,100);
  TH1F* h_trk_nstdown = new TH1F("h_trk_nstdown", "", 100,0,100);
  TH1F* h_trk_tsdainter = new TH1F("h_trk_tsdainter", "", 100,0,100);
  TH1F* h_trk_opainter = new TH1F("h_trk_opainter", "", 100,0,100);
  TH1F* h_trk_firststinter = new TH1F("h_trk_firststinter", "", 100,0,100);
  TH1F* h_trk_chisq = new TH1F("h_trk_chisq", "", 100,0,100);
  TH1F* h_trk_fitcon = new TH1F("h_trk_fitcon", "", 100,0,100);
  TH1F* h_trk_radlen = new TH1F("h_trk_radlen", "", 100,0,100);
  TH1F* h_trk_firsthit = new TH1F("h_trk_firsthit", "", 100,0,100);
  TH1F* h_trk_lasthit = new TH1F("h_trk_lasthit", "", 100,0,100);
  TH1F* h_trk_maxgap = new TH1F("h_trk_maxgap", "", 100,0,100);
  TH1F* h_trk_avggap = new TH1F("h_trk_avggap", "", 100,0,100);
  TH1F* h_trk_avgedep = new TH1F("h_trk_avgedep", "", 100,0,100);

  TH1F* h_trksegs_mom_x = new TH1F("h_trksegs_mom_x", "", 100,0,100);
  TH1F* h_trksegs_mom_y = new TH1F("h_trksegs_mom_y", "", 100,0,100);
  TH1F* h_trksegs_mom_z = new TH1F("h_trksegs_mom_z", "", 100,0,100);
  TH1F* h_trksegs_mom_mag = new TH1F("h_trksegs_mom_mag", "", 100,0,100);
  TH1F* h_trksegs_pos_x = new TH1F("h_trksegs_pos_x", "", 100,0,100);
  TH1F* h_trksegs_pos_y = new TH1F("h_trksegs_pos_y", "", 100,0,100);
  TH1F* h_trksegs_pos_z = new TH1F("h_trksegs_pos_z", "", 100,0,100);
  TH1F* h_trksegs_time = new TH1F("h_trksegs_time", "", 100,0,100);
  TH1F* h_trksegs_dmom = new TH1F("h_trksegs_dmom", "", 100,0,100);
  TH1F* h_trksegs_momerr = new TH1F("h_trksegs_momerr", "", 100,0,100);
  TH1F* h_trksegs_inbounds = new TH1F("h_trksegs_inbounds", "", 100,0,100);
  TH1F* h_trksegs_gap = new TH1F("h_trksegs_gap", "", 100,0,100);
  TH1F* h_trksegs_early = new TH1F("h_trksegs_early", "", 100,0,100);
  TH1F* h_trksegs_late = new TH1F("h_trksegs_late", "", 100,0,100);
  TH1F* h_trksegs_sid = new TH1F("h_trksegs_sid", "", 100,0,100);
  TH1F* h_trksegs_sindex = new TH1F("h_trksegs_sindex", "", 100,0,100);

  TH1F* h_trkmc_valid = new TH1F("h_trkmc_valid", "",100,0,100);
  TH1F* h_trkmc_ndigi = new TH1F("h_trkmc_ndigi", "",100,0,100);
  TH1F* h_trkmc_ndigigood = new TH1F("h_trkmc_ndigigood", "",100,0,100);
  TH1F* h_trkmc_nhits = new TH1F("h_trkmc_nhits", "",100,0,100);
  TH1F* h_trkmc_nactive = new TH1F("h_trkmc_nactive", "",100,0,100);
  TH1F* h_trkmc_nambig = new TH1F("h_trkmc_nambig", "",100,0,100);
  TH1F* h_trkmc_nipaup = new TH1F("h_trkmc_nipaup", "",100,0,100);
  TH1F* h_trkmc_nipadown = new TH1F("h_trkmc_nipadown", "",100,0,100);
  TH1F* h_trkmc_nstup = new TH1F("h_trkmc_nstup", "",100,0,100);
  TH1F* h_trkmc_nstdown = new TH1F("h_trkmc_nstdown", "",100,0,100);
  TH1F* h_trkmc_maxr = new TH1F("h_trkmc_maxr", "",100,0,100);
  TH1F* h_trkmc_rad = new TH1F("h_trkmc_rad", "",100,0,100);
  TH1F* h_trkmc_lam = new TH1F("h_trkmc_lam", "",100,0,100);
  TH1F* h_trkmc_cx = new TH1F("h_trkmc_cx", "",100,0,100);
  TH1F* h_trkmc_cy = new TH1F("h_trkmc_cy", "",100,0,100);
  TH1F* h_trkmc_phi0 = new TH1F("h_trkmc_phi0", "",100,0,100);
  TH1F* h_trkmc_t0 = new TH1F("h_trkmc_t0", "",100,0,100);

  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);

    h_evtinfo_event->Fill(event.evtinfo->event);
    h_evtinfo_subrun->Fill(event.evtinfo->subrun);
    h_evtinfo_run->Fill(event.evtinfo->run);
    h_evtinfo_nprotons->Fill(event.evtinfo->nprotons);
    h_evtinfo_pbtime->Fill(event.evtinfo->pbtime);
    h_evtinfo_pbterr->Fill(event.evtinfo->pbterr);

    h_evtinfomc_nprotons->Fill(event.evtinfomc->nprotons);
    h_evtinfomc_pbtime->Fill(event.evtinfomc->pbtime);

    for (const auto& trk : *(event.trk)) {
      h_trk_status->Fill(trk.status);
      h_trk_goodfit->Fill(trk.goodfit);
      h_trk_seedalg->Fill(trk.seedalg);
      h_trk_fitalg->Fill(trk.fitalg);
      h_trk_pdg->Fill(trk.pdg);
      h_trk_nhits->Fill(trk.nhits);
      h_trk_ndof->Fill(trk.ndof);
      h_trk_nactive->Fill(trk.nactive);
      h_trk_ndouble->Fill(trk.ndouble);
      h_trk_ndactive->Fill(trk.ndactive);
      h_trk_nplanes->Fill(trk.nplanes);
      h_trk_planespan->Fill(trk.planespan);
      h_trk_nnullambig->Fill(trk.nnullambig);
      h_trk_nmat->Fill(trk.nmat);
      h_trk_nmatactive->Fill(trk.nmatactive);
      h_trk_nesel->Fill(trk.nesel);
      h_trk_nrsel->Fill(trk.nrsel);
      h_trk_ntsel->Fill(trk.ntsel);
      h_trk_nbkg->Fill(trk.nbkg);
      h_trk_nsel->Fill(trk.nsel);
      h_trk_nseg->Fill(trk.nseg);
      h_trk_nipaup->Fill(trk.nipaup);
      h_trk_nipadown->Fill(trk.nipadown);
      h_trk_nstup->Fill(trk.nstup);
      h_trk_nstdown->Fill(trk.nstdown);
      h_trk_tsdainter->Fill(trk.tsdainter);
      h_trk_opainter->Fill(trk.opainter);
      h_trk_firststinter->Fill(trk.firststinter);
      h_trk_chisq->Fill(trk.chisq);
      h_trk_fitcon->Fill(trk.fitcon);
      h_trk_radlen->Fill(trk.radlen);
      h_trk_firsthit->Fill(trk.firsthit);
      h_trk_lasthit->Fill(trk.lasthit);
      h_trk_maxgap->Fill(trk.maxgap);
      h_trk_avggap->Fill(trk.avggap);
      h_trk_avgedep->Fill(trk.avgedep);
    }

    for (const auto& trksegs : *(event.trksegs)) {
      for (const auto& trkseg : trksegs) {
        h_trksegs_mom_x->Fill(trkseg.mom.x());
        h_trksegs_mom_y->Fill(trkseg.mom.y());
        h_trksegs_mom_z->Fill(trkseg.mom.z());
        h_trksegs_mom_mag->Fill(trkseg.mom.R());
        h_trksegs_pos_x->Fill(trkseg.pos.x());
        h_trksegs_pos_y->Fill(trkseg.pos.y());
        h_trksegs_pos_z->Fill(trkseg.pos.z());
        h_trksegs_time->Fill(trkseg.time);
        h_trksegs_dmom->Fill(trkseg.dmom);
        h_trksegs_momerr->Fill(trkseg.momerr);
        h_trksegs_inbounds->Fill(trkseg.inbounds);
        h_trksegs_gap->Fill(trkseg.gap);
        h_trksegs_early->Fill(trkseg.early);
        h_trksegs_late->Fill(trkseg.late);
        h_trksegs_sid->Fill(trkseg.sid);
        h_trksegs_sindex->Fill(trkseg.sindex);
      }
    }

    for (const auto& trkmc : *(event.trkmc)) {
      h_trkmc_valid->Fill(trkmc.valid);
      h_trkmc_ndigi->Fill(trkmc.ndigi);
      h_trkmc_ndigigood->Fill(trkmc.ndigigood);
      h_trkmc_nhits->Fill(trkmc.nhits);
      h_trkmc_nactive->Fill(trkmc.nactive);
      h_trkmc_nambig->Fill(trkmc.nambig);
      h_trkmc_nipaup->Fill(trkmc.nipaup);
      h_trkmc_nipadown->Fill(trkmc.nipadown);
      h_trkmc_nstup->Fill(trkmc.nstup);
      h_trkmc_nstdown->Fill(trkmc.nstdown);
      h_trkmc_maxr->Fill(trkmc.maxr);
      h_trkmc_rad->Fill(trkmc.rad);
      h_trkmc_lam->Fill(trkmc.lam);
      h_trkmc_cx->Fill(trkmc.cx);
      h_trkmc_cy->Fill(trkmc.cy);
      h_trkmc_phi0->Fill(trkmc.phi0);
      h_trkmc_t0->Fill(trkmc.t0);
    }
  }

  // // resolution histograms
  // ntuple->Draw("(trksegs[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_all", "", "goff");
  // ntuple->Draw("(trksegs[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_ent", "trkmcvd[].sid==0", "goff");
  // ntuple->Draw("(trksegs[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_mid", "trkmcvd[].sid==1", "goff");
  // ntuple->Draw("(trksegs[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_xit", "trkmcvd[].sid==2", "goff");

  // // trkcalohit histograms
  // ntuple->Draw("trkcalohit.ctime>>h_demtch_ctime_all", "", "goff");
  // ntuple->Draw("trkcalohit.ctime>>h_demtch_ctime_active", "trkcalohit.active==1", "goff");
  // ntuple->Draw("trkcalohit.ctime>>h_demtch_ctime_inactive", "trkcalohit.active==0", "goff");
  // ntuple->Draw("trkcalohit.ctime-trklh.t0>>h_demtch_demfit_dt_ent", "trksegs.sid==0 && trktch.active==1", "goff");

  // // trkcalohitmc histograms
  // ntuple->Draw("trkcalohitmc.nsim>>h_trkcalohitmc_nsim_all", "", "goff");
  // ntuple->Draw("trkcalohitmc.etot>>h_trkcalohitmc_etot_all", "", "goff");
  // ntuple->Draw("trkcalohitmc.tavg>>h_trkcalohitmc_tavg_all", "", "goff");
  // ntuple->Draw("trkcalohitmc.eprimary>>h_trkcalohitmc_eprimary_all", "", "goff");
  // ntuple->Draw("trkcalohitmc.tprimary>>h_trkcalohitmc_tprimary_all", "", "goff");

  // // crv histograms
  // ntuple->Draw("crvsummary.totalPEs>>h_crvsummary_totalPEs_all", "", "goff");
  // ntuple->Draw("crvcoincs.pos.fCoordinates.fX>>h_crvhit_pos_x", "", "goff");
  // ntuple->Draw("crvcoincs.pos.fCoordinates.fY>>h_crvhit_pos_y", "", "goff");
  // ntuple->Draw("crvcoincs.pos.fCoordinates.fZ>>h_crvhit_pos_z", "", "goff");
  // ntuple->Draw("crvcoincsmc.primary.fCoordinates.fX>>h_crvhitmc_primary_x", "", "goff");
  // ntuple->Draw("crvcoincsmc.primary.fCoordinates.fY>>h_crvhitmc_primary_y", "", "goff");
  // ntuple->Draw("crvcoincsmc.primary.fCoordinates.fZ>>h_crvhitmc_primary_z", "", "goff");
  // ntuple->Draw("crvcoincsmc.depositedEnergy>>h_crvhitmc_depostedEnergy", "", "goff");

  // // trkmcsim histograms
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_all", "", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_all", "", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_all", "", "goff");
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  // ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");
  // ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");
  // ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");


  file->Write();
  file->Close();
}
