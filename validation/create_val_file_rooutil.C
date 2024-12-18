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

  TH1F* h_trksegsmc_sid = new TH1F("h_trksegsmc_sid", "", 100,0,100);
  TH1F* h_trksegsmc_sindex = new TH1F("h_trksegsmc_sindex", "", 100,0,100);
  TH1F* h_trksegsmc_time = new TH1F("h_trksegsmc_time", "", 100,0,100);
  TH1F* h_trksegsmc_edep = new TH1F("h_trksegsmc_edep", "", 100,0,100);
  TH1F* h_trksegsmc_path = new TH1F("h_trksegsmc_path", "", 100,0,100);
  TH1F* h_trksegsmc_pos_x = new TH1F("h_trksegsmc_pos_x", "", 100,0,100);
  TH1F* h_trksegsmc_pos_y = new TH1F("h_trksegsmc_pos_y", "", 100,0,100);
  TH1F* h_trksegsmc_pos_z = new TH1F("h_trksegsmc_pos_z", "", 100,0,100);
  TH1F* h_trksegsmc_mom_x = new TH1F("h_trksegsmc_mom_x", "", 100,0,100);
  TH1F* h_trksegsmc_mom_y = new TH1F("h_trksegsmc_mom_y", "", 100,0,100);
  TH1F* h_trksegsmc_mom_z = new TH1F("h_trksegsmc_mom_z", "", 100,0,100);

  TH1F* h_trkcalohit_active = new TH1F("h_trkcalohit_active", "", 100,0,100);
  TH1F* h_trkcalohit_did = new TH1F("h_trkcalohit_did", "", 100,0,100);
  TH1F* h_trkcalohit_poca_x = new TH1F("h_trkcalohit_poca_x", "", 100,0,100);
  TH1F* h_trkcalohit_poca_y = new TH1F("h_trkcalohit_poca_y", "", 100,0,100);
  TH1F* h_trkcalohit_poca_z = new TH1F("h_trkcalohit_poca_z", "", 100,0,100);
  TH1F* h_trkcalohit_mom_x = new TH1F("h_trkcalohit_mom_x", "", 100,0,100);
  TH1F* h_trkcalohit_mom_y = new TH1F("h_trkcalohit_mom_y", "", 100,0,100);
  TH1F* h_trkcalohit_mom_z = new TH1F("h_trkcalohit_mom_z", "", 100,0,100);
  TH1F* h_trkcalohit_cdepth = new TH1F("h_trkcalohit_cdepth", "", 100,0,100);
  TH1F* h_trkcalohit_trkdepth = new TH1F("h_trkcalohit_trkdepth", "", 100,0,100);
  TH1F* h_trkcalohit_dphidot = new TH1F("h_trkcalohit_dphidot", "", 100,0,100);
  TH1F* h_trkcalohit_doca = new TH1F("h_trkcalohit_doca", "", 100,0,100);
  TH1F* h_trkcalohit_dt = new TH1F("h_trkcalohit_dt", "", 100,0,100);
  TH1F* h_trkcalohit_ptoca = new TH1F("h_trkcalohit_ptoca", "", 100,0,100);
  TH1F* h_trkcalohit_tocavar = new TH1F("h_trkcalohit_tocavar", "", 100,0,100);
  TH1F* h_trkcalohit_tresid = new TH1F("h_trkcalohit_tresid", "", 100,0,100);
  TH1F* h_trkcalohit_tresidmvar = new TH1F("h_trkcalohit_tresidmvar", "", 100,0,100);
  TH1F* h_trkcalohit_tresidpvar = new TH1F("h_trkcalohit_tresidpvar", "", 100,0,100);
  TH1F* h_trkcalohit_ctime = new TH1F("h_trkcalohit_ctime", "", 100,0,100);
  TH1F* h_trkcalohit_ctimeerr = new TH1F("h_trkcalohit_ctimeerr", "", 100,0,100);
  TH1F* h_trkcalohit_csize = new TH1F("h_trkcalohit_csize", "", 100,0,100);
  TH1F* h_trkcalohit_edep = new TH1F("h_trkcalohit_edep", "", 100,0,100);
  TH1F* h_trkcalohit_edeperr = new TH1F("h_trkcalohit_edeperr", "", 100,0,100);

  TH1F* h_trkcalohitmc_nsim = new TH1F("h_trkcalohitmc_nsim", "", 100,0,100);
  TH1F* h_trkcalohitmc_etot = new TH1F("h_trkcalohitmc_etot", "", 100,0,100);
  TH1F* h_trkcalohitmc_tavg = new TH1F("h_trkcalohitmc_tavg", "", 100,0,100);
  TH1F* h_trkcalohitmc_eprimary = new TH1F("h_trkcalohitmc_eprimary", "", 100,0,100);
  TH1F* h_trkcalohitmc_tprimary = new TH1F("h_trkcalohitmc_tprimary", "", 100,0,100);
  TH1F* h_trkcalohitmc_prel = new TH1F("h_trkcalohitmc_prel", "", 100,0,100);

  TH1F* h_crvcoincs_sectorType = new TH1F("h_crvcoincs_sectorType", "", 100,0,100);
  TH1F* h_crvcoincs_pos_x = new TH1F("h_crvcoincs_pos_x", "", 100,0,100);
  TH1F* h_crvcoincs_pos_y = new TH1F("h_crvcoincs_pos_y", "", 100,0,100);
  TH1F* h_crvcoincs_pos_z = new TH1F("h_crvcoincs_pos_z", "", 100,0,100);
  TH1F* h_crvcoincs_timeStart = new TH1F("h_crvcoincs_timeStart", "", 100,0,100);
  TH1F* h_crvcoincs_timeEnd = new TH1F("h_crvcoincs_timeEnd", "", 100,0,100);
  TH1F* h_crvcoincs_time = new TH1F("h_crvcoincs_time", "", 100,0,100);
  TH1F* h_crvcoincs_PEs = new TH1F("h_crvcoincs_PEs", "", 100,0,100);
  TH1F* h_crvcoincs_PEsPerLayer = new TH1F("h_crvcoincs_PEsPerLayer", "", 100,0,100);
  TH1F* h_crvcoincs_nHits = new TH1F("h_crvcoincs_nHits", "", 100,0,100);
  TH1F* h_crvcoincs_nLayers = new TH1F("h_crvcoincs_nLayers", "", 100,0,100);
  TH1F* h_crvcoincs_angle = new TH1F("h_crvcoincs_angle", "", 100,0,100);

  TH1F* h_crvcoincsmc_valid = new TH1F("h_crvcoincsmc_valid", "", 100,0,100);
  TH1F* h_crvcoincsmc_pdgId = new TH1F("h_crvcoincsmc_pdgId", "", 100,0,100);
  TH1F* h_crvcoincsmc_primaryPdgId = new TH1F("h_crvcoincsmc_primaryPdgId", "", 100,0,100);
  TH1F* h_crvcoincsmc_primaryE = new TH1F("h_crvcoincsmc_primaryE", "", 100,0,100);
  TH1F* h_crvcoincsmc_primary_x = new TH1F("h_crvcoincsmc_primary_x", "", 100,0,100);
  TH1F* h_crvcoincsmc_primary_y = new TH1F("h_crvcoincsmc_primary_y", "", 100,0,100);
  TH1F* h_crvcoincsmc_primary_z = new TH1F("h_crvcoincsmc_primary_z", "", 100,0,100);
  TH1F* h_crvcoincsmc_parentPdgId = new TH1F("h_crvcoincsmc_parentPdgId", "", 100,0,100);
  TH1F* h_crvcoincsmc_parentE = new TH1F("h_crvcoincsmc_parentE", "", 100,0,100);
  TH1F* h_crvcoincsmc_parent_x = new TH1F("h_crvcoincsmc_parent_x", "", 100,0,100);
  TH1F* h_crvcoincsmc_parent_y = new TH1F("h_crvcoincsmc_parent_y", "", 100,0,100);
  TH1F* h_crvcoincsmc_parent_z = new TH1F("h_crvcoincsmc_parent_z", "", 100,0,100);
  TH1F* h_crvcoincsmc_gparentPdgId = new TH1F("h_crvcoincsmc_gparentPdgId", "", 100,0,100);
  TH1F* h_crvcoincsmc_gparentE = new TH1F("h_crvcoincsmc_gparentE", "", 100,0,100);
  TH1F* h_crvcoincsmc_gparent_x = new TH1F("h_crvcoincsmc_gparent_x", "", 100,0,100);
  TH1F* h_crvcoincsmc_gparent_y = new TH1F("h_crvcoincsmc_gparent_y", "", 100,0,100);
  TH1F* h_crvcoincsmc_gparent_z = new TH1F("h_crvcoincsmc_gparent_z", "", 100,0,100);
  TH1F* h_crvcoincsmc_pos_x = new TH1F("h_crvcoincsmc_pos_x", "", 100,0,100);
  TH1F* h_crvcoincsmc_pos_y = new TH1F("h_crvcoincsmc_pos_y", "", 100,0,100);
  TH1F* h_crvcoincsmc_pos_z = new TH1F("h_crvcoincsmc_pos_z", "", 100,0,100);
  TH1F* h_crvcoincsmc_time = new TH1F("h_crvcoincsmc_time", "", 100,0,100);
  TH1F* h_crvcoincsmc_depositedEnergy = new TH1F("h_crvcoincsmc_depositedEnergy", "", 100,0,100);

  TH1F* h_trkmcsim_valid = new TH1F("h_trkmcsim_valid", "", 100,0,100);
  TH1F* h_trkmcsim_nhits = new TH1F("h_trkmcsim_nhits", "", 100,0,100);
  TH1F* h_trkmcsim_nactive = new TH1F("h_trkmcsim_nactive", "", 100,0,100);
  TH1F* h_trkmcsim_rank = new TH1F("h_trkmcsim_rank", "", 100,0,100);
  TH1F* h_trkmcsim_pdg = new TH1F("h_trkmcsim_pdg", "", 100,0,100);
  TH1F* h_trkmcsim_startCode = new TH1F("h_trkmcsim_startCode", "", 100,0,100);
  TH1F* h_trkmcsim_stopCode = new TH1F("h_trkmcsim_stopCode", "", 100,0,100);
  TH1F* h_trkmcsim_gen = new TH1F("h_trkmcsim_gen", "", 100,0,100);
  TH1F* h_trkmcsim_time = new TH1F("h_trkmcsim_time", "", 100,0,100);
  TH1F* h_trkmcsim_index = new TH1F("h_trkmcsim_index", "", 100,0,100);
  TH1F* h_trkmcsim_mom_x = new TH1F("h_trkmcsim_mom_x", "", 100,0,100);
  TH1F* h_trkmcsim_mom_y = new TH1F("h_trkmcsim_mom_y", "", 100,0,100);
  TH1F* h_trkmcsim_mom_z = new TH1F("h_trkmcsim_mom_z", "", 100,0,100);
  TH1F* h_trkmcsim_pos_x = new TH1F("h_trkmcsim_pos_x", "", 100,0,100);
  TH1F* h_trkmcsim_pos_y = new TH1F("h_trkmcsim_pos_y", "", 100,0,100);
  TH1F* h_trkmcsim_pos_z = new TH1F("h_trkmcsim_pos_z", "", 100,0,100);
  TH1F* h_trkmcsim_endmom_x = new TH1F("h_trkmcsim_endmom_x", "", 100,0,100);
  TH1F* h_trkmcsim_endmom_y = new TH1F("h_trkmcsim_endmom_y", "", 100,0,100);
  TH1F* h_trkmcsim_endmom_z = new TH1F("h_trkmcsim_endmom_z", "", 100,0,100);
  TH1F* h_trkmcsim_endpos_x = new TH1F("h_trkmcsim_endpos_x", "", 100,0,100);
  TH1F* h_trkmcsim_endpos_y = new TH1F("h_trkmcsim_endpos_y", "", 100,0,100);
  TH1F* h_trkmcsim_endpos_z = new TH1F("h_trkmcsim_endpos_z", "", 100,0,100);
  TH1F* h_trkmcsim_prirel_rel = new TH1F("h_trkmcsim_prirel_rel", "", 100,0,100);
  TH1F* h_trkmcsim_prirel_rem = new TH1F("h_trkmcsim_prirel_rem", "", 100,0,100);
  TH1F* h_trkmcsim_trkrel_rel = new TH1F("h_trkmcsim_trkrel_rel", "", 100,0,100);
  TH1F* h_trkmcsim_trkrel_rem = new TH1F("h_trkmcsim_trkrel_rem", "", 100,0,100);

  TH1F* h_trkqual_valid = new TH1F("h_trkqual_valid", "", 100,0,100);
  TH1F* h_trkqual_result = new TH1F("h_trkqual_result", "", 100,0,100);

  TH1F* h_trksegpars_lh_maxr = new TH1F("h_trksegpars_lh_maxr", "", 100,0,100);
  TH1F* h_trksegpars_lh_d0 = new TH1F("h_trksegpars_lh_d0", "", 100,0,100);
  TH1F* h_trksegpars_lh_tanDip = new TH1F("h_trksegpars_lh_tanDip", "", 100,0,100);
  TH1F* h_trksegpars_lh_rad = new TH1F("h_trksegpars_lh_rad", "", 100,0,100);
  TH1F* h_trksegpars_lh_lam = new TH1F("h_trksegpars_lh_lam", "", 100,0,100);
  TH1F* h_trksegpars_lh_cx = new TH1F("h_trksegpars_lh_cx", "", 100,0,100);
  TH1F* h_trksegpars_lh_cy = new TH1F("h_trksegpars_lh_cy", "", 100,0,100);
  TH1F* h_trksegpars_lh_phi0 = new TH1F("h_trksegpars_lh_phi0", "", 100,0,100);
  TH1F* h_trksegpars_lh_t0 = new TH1F("h_trksegpars_lh_t0", "", 100,0,100);
  TH1F* h_trksegpars_lh_raderr = new TH1F("h_trksegpars_lh_raderr", "", 100,0,100);
  TH1F* h_trksegpars_lh_lamerr = new TH1F("h_trksegpars_lh_lamerr", "", 100,0,100);
  TH1F* h_trksegpars_lh_cxerr = new TH1F("h_trksegpars_lh_cxerr", "", 100,0,100);
  TH1F* h_trksegpars_lh_cyerr = new TH1F("h_trksegpars_lh_cyerr", "", 100,0,100);
  TH1F* h_trksegpars_lh_phi0err = new TH1F("h_trksegpars_lh_phi0err", "", 100,0,100);
  TH1F* h_trksegpars_lh_t0err = new TH1F("h_trksegpars_lh_t0err", "", 100,0,100);

  TH1F* h_trksegpars_ch_d0 = new TH1F("h_trksegpars_ch_d0", "", 100,0,100);
  TH1F* h_trksegpars_ch_phi0 = new TH1F("h_trksegpars_ch_phi0", "", 100,0,100);
  TH1F* h_trksegpars_ch_omega = new TH1F("h_trksegpars_ch_omega", "", 100,0,100);
  TH1F* h_trksegpars_ch_z0 = new TH1F("h_trksegpars_ch_z0", "", 100,0,100);
  TH1F* h_trksegpars_ch_tanDip = new TH1F("h_trksegpars_ch_tanDip", "", 100,0,100);
  TH1F* h_trksegpars_ch_t0 = new TH1F("h_trksegpars_ch_t0", "", 100,0,100);
  TH1F* h_trksegpars_ch_d0err = new TH1F("h_trksegpars_ch_d0err", "", 100,0,100);
  TH1F* h_trksegpars_ch_phi0err = new TH1F("h_trksegpars_ch_phi0err", "", 100,0,100);
  TH1F* h_trksegpars_ch_omegaerr = new TH1F("h_trksegpars_ch_omegaerr", "", 100,0,100);
  TH1F* h_trksegpars_ch_z0err = new TH1F("h_trksegpars_ch_z0err", "", 100,0,100);
  TH1F* h_trksegpars_ch_tanDiperr = new TH1F("h_trksegpars_ch_tanDiperr", "", 100,0,100);
  TH1F* h_trksegpars_ch_t0err = new TH1F("h_trksegpars_ch_t0err", "", 100,0,100);
  TH1F* h_trksegpars_ch_maxr = new TH1F("h_trksegpars_ch_maxr", "", 100,0,100);

  TH1F* h_trksegpars_kl_d0 = new TH1F("h_trksegpars_kl_d0", "", 100,0,100);
  TH1F* h_trksegpars_kl_phi0 = new TH1F("h_trksegpars_kl_phi0", "", 100,0,100);
  TH1F* h_trksegpars_kl_z0 = new TH1F("h_trksegpars_kl_z0", "", 100,0,100);
  TH1F* h_trksegpars_kl_theta = new TH1F("h_trksegpars_kl_theta", "", 100,0,100);
  TH1F* h_trksegpars_kl_mom = new TH1F("h_trksegpars_kl_mom", "", 100,0,100);
  TH1F* h_trksegpars_kl_t0 = new TH1F("h_trksegpars_kl_t0", "", 100,0,100);
  TH1F* h_trksegpars_kl_d0err = new TH1F("h_trksegpars_kl_d0err", "", 100,0,100);
  TH1F* h_trksegpars_kl_phi0err = new TH1F("h_trksegpars_kl_phi0err", "", 100,0,100);
  TH1F* h_trksegpars_kl_z0err = new TH1F("h_trksegpars_kl_z0err", "", 100,0,100);
  TH1F* h_trksegpars_kl_thetaerr = new TH1F("h_trksegpars_kl_thetaerr", "", 100,0,100);
  TH1F* h_trksegpars_kl_momerr = new TH1F("h_trksegpars_kl_momerr", "", 100,0,100);
  TH1F* h_trksegpars_kl_t0err = new TH1F("h_trksegpars_kl_t0err", "", 100,0,100);

  TH1F* h_trkhits_plane = new TH1F("h_trkhits_plane", "", 100,0,100);
  TH1F* h_trkhits_panel = new TH1F("h_trkhits_panel", "", 100,0,100);
  TH1F* h_trkhits_layer = new TH1F("h_trkhits_layer", "", 100,0,100);
  TH1F* h_trkhits_straw = new TH1F("h_trkhits_straw", "", 100,0,100);
  TH1F* h_trkhits_state = new TH1F("h_trkhits_state", "", 100,0,100);
  TH1F* h_trkhits_algo = new TH1F("h_trkhits_algo", "", 100,0,100);
  TH1F* h_trkhits_frozen = new TH1F("h_trkhits_frozen", "", 100,0,100);
  TH1F* h_trkhits_usetot = new TH1F("h_trkhits_usetot", "", 100,0,100);
  TH1F* h_trkhits_usedriftdt = new TH1F("h_trkhits_usedriftdt", "", 100,0,100);
  TH1F* h_trkhits_useabsdt = new TH1F("h_trkhits_useabsdt", "", 100,0,100);
  TH1F* h_trkhits_usendvar = new TH1F("h_trkhits_usendvar", "", 100,0,100);
  TH1F* h_trkhits_bkgqual = new TH1F("h_trkhits_bkgqual", "", 100,0,100);
  TH1F* h_trkhits_signqual = new TH1F("h_trkhits_signqual", "", 100,0,100);
  TH1F* h_trkhits_driftqual = new TH1F("h_trkhits_driftqual", "", 100,0,100);
  TH1F* h_trkhits_chi2qual = new TH1F("h_trkhits_chi2qual", "", 100,0,100);
  TH1F* h_trkhits_earlyend = new TH1F("h_trkhits_earlyend", "", 100,0,100);
  TH1F* h_trkhits_edep = new TH1F("h_trkhits_edep", "", 100,0,100);
  TH1F* h_trkhits_wdist = new TH1F("h_trkhits_wdist", "", 100,0,100);
  TH1F* h_trkhits_werr = new TH1F("h_trkhits_werr", "", 100,0,100);
  TH1F* h_trkhits_tottdrift = new TH1F("h_trkhits_tottdrift", "", 100,0,100);
  TH1F* h_trkhits_etime_0 = new TH1F("h_trkhits_etime_0", "", 100,0,100);
  TH1F* h_trkhits_etime_1 = new TH1F("h_trkhits_etime_1", "", 100,0,100);
  TH1F* h_trkhits_tot_0 = new TH1F("h_trkhits_tot_0", "", 100,0,100);
  TH1F* h_trkhits_tot_1 = new TH1F("h_trkhits_tot_1", "", 100,0,100);
  TH1F* h_trkhits_ptoca = new TH1F("h_trkhits_ptoca", "", 100,0,100);
  TH1F* h_trkhits_stoca = new TH1F("h_trkhits_stoca", "", 100,0,100);
  TH1F* h_trkhits_rdoca = new TH1F("h_trkhits_rdoca", "", 100,0,100);
  TH1F* h_trkhits_rdocavar = new TH1F("h_trkhits_rdocavar", "", 100,0,100);
  TH1F* h_trkhits_rdt = new TH1F("h_trkhits_rdt", "", 100,0,100);
  TH1F* h_trkhits_rtocavar = new TH1F("h_trkhits_rtocavar", "", 100,0,100);
  TH1F* h_trkhits_udoca = new TH1F("h_trkhits_udoca", "", 100,0,100);
  TH1F* h_trkhits_udocavar = new TH1F("h_trkhits_udocavar", "", 100,0,100);
  TH1F* h_trkhits_udt = new TH1F("h_trkhits_udt", "", 100,0,100);
  TH1F* h_trkhits_utocavar = new TH1F("h_trkhits_utocavar", "", 100,0,100);
  TH1F* h_trkhits_rupos = new TH1F("h_trkhits_rupos", "", 100,0,100);
  TH1F* h_trkhits_uupos = new TH1F("h_trkhits_uupos", "", 100,0,100);
  TH1F* h_trkhits_rdrift = new TH1F("h_trkhits_rdrift", "", 100,0,100);
  TH1F* h_trkhits_cdrift = new TH1F("h_trkhits_cdrift", "", 100,0,100);
  TH1F* h_trkhits_sderr = new TH1F("h_trkhits_sderr", "", 100,0,100);
  TH1F* h_trkhits_uderr = new TH1F("h_trkhits_uderr", "", 100,0,100);
  TH1F* h_trkhits_dvel = new TH1F("h_trkhits_dvel", "", 100,0,100);
  TH1F* h_trkhits_lang = new TH1F("h_trkhits_lang", "", 100,0,100);
  TH1F* h_trkhits_utresid = new TH1F("h_trkhits_utresid", "", 100,0,100);
  TH1F* h_trkhits_utresidmvar = new TH1F("h_trkhits_utresidmvar", "", 100,0,100);
  TH1F* h_trkhits_utresidpvar = new TH1F("h_trkhits_utresidpvar", "", 100,0,100);
  TH1F* h_trkhits_udresid = new TH1F("h_trkhits_udresid", "", 100,0,100);
  TH1F* h_trkhits_udresidmvar = new TH1F("h_trkhits_udresidmvar", "", 100,0,100);
  TH1F* h_trkhits_udresidpvar = new TH1F("h_trkhits_udresidpvar", "", 100,0,100);
  TH1F* h_trkhits_rtresid = new TH1F("h_trkhits_rtresid", "", 100,0,100);
  TH1F* h_trkhits_rtresidmvar = new TH1F("h_trkhits_rtresidmvar", "", 100,0,100);
  TH1F* h_trkhits_rtresidpvar = new TH1F("h_trkhits_rtresidpvar", "", 100,0,100);
  TH1F* h_trkhits_rdresid = new TH1F("h_trkhits_rdresid", "", 100,0,100);
  TH1F* h_trkhits_rdresidmvar = new TH1F("h_trkhits_rdresidmvar", "", 100,0,100);
  TH1F* h_trkhits_rdresidpvar = new TH1F("h_trkhits_rdresidpvar", "", 100,0,100);
  TH1F* h_trkhits_wdot = new TH1F("h_trkhits_wdot", "", 100,0,100);
  TH1F* h_trkhits_poca_x = new TH1F("h_trkhits_poca_x", "", 100,0,100);
  TH1F* h_trkhits_poca_y = new TH1F("h_trkhits_poca_y", "", 100,0,100);
  TH1F* h_trkhits_poca_z = new TH1F("h_trkhits_poca_z", "", 100,0,100);
  TH1F* h_trkhits_uwirephi = new TH1F("h_trkhits_uwirephi", "", 100,0,100);
  TH1F* h_trkhits_ustrawdist = new TH1F("h_trkhits_ustrawdist", "", 100,0,100);
  TH1F* h_trkhits_ustrawphi = new TH1F("h_trkhits_ustrawphi", "", 100,0,100);
  TH1F* h_trkhits_dhit = new TH1F("h_trkhits_dhit", "", 100,0,100);
  TH1F* h_trkhits_dactive = new TH1F("h_trkhits_dactive", "", 100,0,100);

  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);

    std::cout << "Creating evtinfo histograms..." << std::endl;
    h_evtinfo_event->Fill(event.evtinfo->event);
    h_evtinfo_subrun->Fill(event.evtinfo->subrun);
    h_evtinfo_run->Fill(event.evtinfo->run);
    h_evtinfo_nprotons->Fill(event.evtinfo->nprotons);
    h_evtinfo_pbtime->Fill(event.evtinfo->pbtime);
    h_evtinfo_pbterr->Fill(event.evtinfo->pbterr);

    h_evtinfomc_nprotons->Fill(event.evtinfomc->nprotons);
    h_evtinfomc_pbtime->Fill(event.evtinfomc->pbtime);

    std::cout << "Creating trk histograms..." << std::endl;
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

    std::cout << "Creating trkseg histograms..." << std::endl;
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

    std::cout << "Creating trkmc histograms..." << std::endl;
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

    std::cout << "Creating trksegsmc histograms..." << std::endl;
    for (const auto& trksegsmc : *(event.trksegsmc)) {
      for (const auto& trksegmc : trksegsmc) {
        h_trksegsmc_sid->Fill(trksegmc.sid);
        h_trksegsmc_sindex->Fill(trksegmc.sindex);
        h_trksegsmc_time->Fill(trksegmc.time);
        h_trksegsmc_edep->Fill(trksegmc.edep);
        h_trksegsmc_path->Fill(trksegmc.path);
        h_trksegsmc_pos_x->Fill(trksegmc.pos.x());
        h_trksegsmc_pos_y->Fill(trksegmc.pos.y());
        h_trksegsmc_pos_z->Fill(trksegmc.pos.z());
        h_trksegsmc_mom_x->Fill(trksegmc.mom.x());
        h_trksegsmc_mom_y->Fill(trksegmc.mom.y());
        h_trksegsmc_mom_z->Fill(trksegmc.mom.z());
      }
    }

    std::cout << "Creating trkcalohit histograms..." << std::endl;
    for (const auto& trkcalohit : *(event.trkcalohit)) {
      h_trkcalohit_active->Fill(trkcalohit.active);
      h_trkcalohit_did->Fill(trkcalohit.did);
      h_trkcalohit_poca_x->Fill(trkcalohit.poca.x());
      h_trkcalohit_poca_y->Fill(trkcalohit.poca.y());
      h_trkcalohit_poca_z->Fill(trkcalohit.poca.z());
      h_trkcalohit_mom_x->Fill(trkcalohit.mom.x());
      h_trkcalohit_mom_y->Fill(trkcalohit.mom.y());
      h_trkcalohit_mom_z->Fill(trkcalohit.mom.z());
      h_trkcalohit_cdepth->Fill(trkcalohit.cdepth);
      h_trkcalohit_trkdepth->Fill(trkcalohit.trkdepth);
      h_trkcalohit_dphidot->Fill(trkcalohit.dphidot);
      h_trkcalohit_doca->Fill(trkcalohit.doca);
      h_trkcalohit_dt->Fill(trkcalohit.dt);
      h_trkcalohit_ptoca->Fill(trkcalohit.ptoca);
      h_trkcalohit_tocavar->Fill(trkcalohit.tocavar);
      h_trkcalohit_tresid->Fill(trkcalohit.tresid);
      h_trkcalohit_tresidmvar->Fill(trkcalohit.tresidmvar);
      h_trkcalohit_tresidpvar->Fill(trkcalohit.tresidpvar);
      h_trkcalohit_ctime->Fill(trkcalohit.ctime);
      h_trkcalohit_ctimeerr->Fill(trkcalohit.ctimeerr);
      h_trkcalohit_csize->Fill(trkcalohit.csize);
      h_trkcalohit_edep->Fill(trkcalohit.edep);
      h_trkcalohit_edeperr->Fill(trkcalohit.edeperr);
    }

    std::cout << "Creating trkcalohitmc histograms..." << std::endl;
    for (const auto& trkcalohitmc : *(event.trkcalohitmc)) {
      h_trkcalohitmc_nsim->Fill(trkcalohitmc.nsim);
      h_trkcalohitmc_etot->Fill(trkcalohitmc.etot);
      h_trkcalohitmc_tavg->Fill(trkcalohitmc.tavg);
      h_trkcalohitmc_eprimary->Fill(trkcalohitmc.eprimary);
      h_trkcalohitmc_tprimary->Fill(trkcalohitmc.tprimary);
      h_trkcalohitmc_prel->Fill(trkcalohitmc.prel.relationship());
    }

    std::cout << "Creating crvcoinc histograms..." << std::endl;
    for (const auto& crvcoinc : *(event.crvcoincs)) {
      h_crvcoincs_sectorType->Fill(crvcoinc.sectorType);
      h_crvcoincs_pos_x->Fill(crvcoinc.pos.x());
      h_crvcoincs_pos_y->Fill(crvcoinc.pos.y());
      h_crvcoincs_pos_z->Fill(crvcoinc.pos.z());
      h_crvcoincs_timeStart->Fill(crvcoinc.timeStart);
      h_crvcoincs_timeEnd->Fill(crvcoinc.timeEnd);
      h_crvcoincs_time->Fill(crvcoinc.time);
      h_crvcoincs_PEs->Fill(crvcoinc.PEs);
      for (const auto& layer_PEs : crvcoinc.PEsPerLayer) {
        h_crvcoincs_PEsPerLayer->Fill(layer_PEs);
      }
      h_crvcoincs_nHits->Fill(crvcoinc.nHits);
      h_crvcoincs_nLayers->Fill(crvcoinc.nLayers);
      h_crvcoincs_angle->Fill(crvcoinc.angle);
    }

    std::cout << "Creating crvcoincmc histograms..." << std::endl;
    for (const auto& crvcoincmc : *(event.crvcoincsmc)) {
      h_crvcoincsmc_valid->Fill(crvcoincmc.valid);
      h_crvcoincsmc_pdgId->Fill(crvcoincmc.pdgId);
      h_crvcoincsmc_primaryPdgId->Fill(crvcoincmc.primaryPdgId);
      h_crvcoincsmc_primaryE->Fill(crvcoincmc.primaryE);
      h_crvcoincsmc_primary_x->Fill(crvcoincmc.primary.x());
      h_crvcoincsmc_primary_y->Fill(crvcoincmc.primary.y());
      h_crvcoincsmc_primary_z->Fill(crvcoincmc.primary.z());
      h_crvcoincsmc_parentPdgId->Fill(crvcoincmc.parentPdgId);
      h_crvcoincsmc_parentE->Fill(crvcoincmc.parentE);
      h_crvcoincsmc_parent_x->Fill(crvcoincmc.parent.x());
      h_crvcoincsmc_parent_y->Fill(crvcoincmc.parent.y());
      h_crvcoincsmc_parent_z->Fill(crvcoincmc.parent.z());
      h_crvcoincsmc_gparentPdgId->Fill(crvcoincmc.gparentPdgId);
      h_crvcoincsmc_gparentE->Fill(crvcoincmc.gparentE);
      h_crvcoincsmc_gparent_x->Fill(crvcoincmc.gparent.x());
      h_crvcoincsmc_gparent_y->Fill(crvcoincmc.gparent.y());
      h_crvcoincsmc_gparent_z->Fill(crvcoincmc.gparent.z());
      h_crvcoincsmc_pos_x->Fill(crvcoincmc.pos.x());
      h_crvcoincsmc_pos_y->Fill(crvcoincmc.pos.y());
      h_crvcoincsmc_pos_z->Fill(crvcoincmc.pos.z());
      h_crvcoincsmc_time->Fill(crvcoincmc.time);
      h_crvcoincsmc_depositedEnergy->Fill(crvcoincmc.depositedEnergy);
    }

    std::cout << "Creating trkmcsim histograms..." << std::endl;
    for (const auto& trkmcsims : *(event.trkmcsim)) {
      for (const auto& trkmcsim : trkmcsims) {
        h_trkmcsim_valid->Fill(trkmcsim.valid);
        h_trkmcsim_nhits->Fill(trkmcsim.nhits);
        h_trkmcsim_nactive->Fill(trkmcsim.nactive);
        h_trkmcsim_rank->Fill(trkmcsim.rank);
        h_trkmcsim_pdg->Fill(trkmcsim.pdg);
        h_trkmcsim_startCode->Fill(trkmcsim.startCode);
        h_trkmcsim_stopCode->Fill(trkmcsim.stopCode);
        h_trkmcsim_gen->Fill(trkmcsim.gen);
        h_trkmcsim_time->Fill(trkmcsim.time);
        h_trkmcsim_index->Fill(trkmcsim.index);
        h_trkmcsim_mom_x->Fill(trkmcsim.mom.x());
        h_trkmcsim_mom_y->Fill(trkmcsim.mom.y());
        h_trkmcsim_mom_z->Fill(trkmcsim.mom.z());
        h_trkmcsim_pos_x->Fill(trkmcsim.pos.x());
        h_trkmcsim_pos_y->Fill(trkmcsim.pos.y());
        h_trkmcsim_pos_z->Fill(trkmcsim.pos.z());
        h_trkmcsim_endmom_x->Fill(trkmcsim.endmom.x());
        h_trkmcsim_endmom_y->Fill(trkmcsim.endmom.y());
        h_trkmcsim_endmom_z->Fill(trkmcsim.endmom.z());
        h_trkmcsim_endpos_x->Fill(trkmcsim.endpos.x());
        h_trkmcsim_endpos_y->Fill(trkmcsim.endpos.y());
        h_trkmcsim_endpos_z->Fill(trkmcsim.endpos.z());
        h_trkmcsim_prirel_rel->Fill(trkmcsim.prirel.relationship());
        h_trkmcsim_prirel_rem->Fill(trkmcsim.prirel.removal());
        h_trkmcsim_trkrel_rel->Fill(trkmcsim.trkrel.relationship());
        h_trkmcsim_trkrel_rem->Fill(trkmcsim.trkrel.removal());
      }
    }

    std::cout << "Creating trkqual histograms..." << std::endl;
    for (const auto& trkqual : *(event.trkqual)) {
      h_trkqual_valid->Fill(trkqual.valid);
      h_trkqual_result->Fill(trkqual.result);
    }

    if (event.trksegpars_lh != nullptr) { // might not have this branch
      std::cout << "Creating trksegpars_lh histograms..." << std::endl;
      for (const auto& track : *(event.trksegpars_lh)) {
        for (const auto& trksegpars_lh : track) {
          h_trksegpars_lh_maxr->Fill(trksegpars_lh.maxr);
          h_trksegpars_lh_d0->Fill(trksegpars_lh.d0);
          h_trksegpars_lh_tanDip->Fill(trksegpars_lh.tanDip);
          h_trksegpars_lh_rad->Fill(trksegpars_lh.rad);
          h_trksegpars_lh_lam->Fill(trksegpars_lh.lam);
          h_trksegpars_lh_cx->Fill(trksegpars_lh.cx);
          h_trksegpars_lh_cy->Fill(trksegpars_lh.cy);
          h_trksegpars_lh_phi0->Fill(trksegpars_lh.phi0);
          h_trksegpars_lh_t0->Fill(trksegpars_lh.t0);
          h_trksegpars_lh_raderr->Fill(trksegpars_lh.raderr);
          h_trksegpars_lh_lamerr->Fill(trksegpars_lh.lamerr);
          h_trksegpars_lh_cxerr->Fill(trksegpars_lh.cxerr);
          h_trksegpars_lh_cyerr->Fill(trksegpars_lh.cyerr);
          h_trksegpars_lh_phi0err->Fill(trksegpars_lh.phi0err);
          h_trksegpars_lh_t0err->Fill(trksegpars_lh.t0err);
        }
      }
    }

    if (event.trksegpars_ch != nullptr) { // might not have this branch
      std::cout << "Creating trksegpars_ch histograms..." << std::endl;
      for (const auto& track : *(event.trksegpars_ch)) {
        for (const auto& trksegpars_ch : track) {
          h_trksegpars_ch_d0->Fill(trksegpars_ch.d0);
          h_trksegpars_ch_phi0->Fill(trksegpars_ch.phi0);
          h_trksegpars_ch_omega->Fill(trksegpars_ch.omega);
          h_trksegpars_ch_z0->Fill(trksegpars_ch.z0);
          h_trksegpars_ch_tanDip->Fill(trksegpars_ch.tanDip);
          h_trksegpars_ch_t0->Fill(trksegpars_ch.t0);
          h_trksegpars_ch_d0err->Fill(trksegpars_ch.d0err);
          h_trksegpars_ch_phi0err->Fill(trksegpars_ch.phi0err);
          h_trksegpars_ch_omegaerr->Fill(trksegpars_ch.omegaerr);
          h_trksegpars_ch_z0err->Fill(trksegpars_ch.z0err);
          h_trksegpars_ch_tanDiperr->Fill(trksegpars_ch.tanDiperr);
          h_trksegpars_ch_t0err->Fill(trksegpars_ch.t0err);
          h_trksegpars_ch_maxr->Fill(trksegpars_ch.maxr);
        }
      }
    }

    if (event.trksegpars_kl != nullptr) { // might not have this branch
      std::cout << "Creating trksegpars_kl histograms..." << std::endl;
      for (const auto& track : *(event.trksegpars_kl)) {
        for (const auto& trksegpars_kl : track) {
          h_trksegpars_kl_d0->Fill(trksegpars_kl.d0);
          h_trksegpars_kl_phi0->Fill(trksegpars_kl.phi0);
          h_trksegpars_kl_z0->Fill(trksegpars_kl.z0);
          h_trksegpars_kl_theta->Fill(trksegpars_kl.theta);
          h_trksegpars_kl_mom->Fill(trksegpars_kl.mom);
          h_trksegpars_kl_t0->Fill(trksegpars_kl.t0);
          h_trksegpars_kl_d0err->Fill(trksegpars_kl.d0err);
          h_trksegpars_kl_phi0err->Fill(trksegpars_kl.phi0err);
          h_trksegpars_kl_z0err->Fill(trksegpars_kl.z0err);
          h_trksegpars_kl_thetaerr->Fill(trksegpars_kl.thetaerr);
          h_trksegpars_kl_momerr->Fill(trksegpars_kl.momerr);
          h_trksegpars_kl_t0err->Fill(trksegpars_kl.t0err);
        }
      }
    }

    if (event.trkhits != nullptr) { // might not have this branch
      std::cout << "Creating trkhits histograms..." << std::endl;
      for (const auto& trkhits : *(event.trkhits)) {
        for (const auto& trkhit : trkhits) {
          h_trkhits_plane->Fill(trkhit.plane);
          h_trkhits_panel->Fill(trkhit.panel);
          h_trkhits_layer->Fill(trkhit.layer);
          h_trkhits_straw->Fill(trkhit.straw);
          h_trkhits_state->Fill(trkhit.state);
          h_trkhits_algo->Fill(trkhit.algo);
          h_trkhits_frozen->Fill(trkhit.frozen);
          h_trkhits_usetot->Fill(trkhit.usetot);
          h_trkhits_usedriftdt->Fill(trkhit.usedriftdt);
          h_trkhits_useabsdt->Fill(trkhit.useabsdt);
          h_trkhits_usendvar->Fill(trkhit.usendvar);
          h_trkhits_bkgqual->Fill(trkhit.bkgqual);
          h_trkhits_signqual->Fill(trkhit.signqual);
          h_trkhits_driftqual->Fill(trkhit.driftqual);
          h_trkhits_chi2qual->Fill(trkhit.chi2qual);
          h_trkhits_earlyend->Fill(trkhit.earlyend);
          h_trkhits_edep->Fill(trkhit.edep);
          h_trkhits_wdist->Fill(trkhit.wdist);
          h_trkhits_werr->Fill(trkhit.werr);
          h_trkhits_tottdrift->Fill(trkhit.tottdrift);
          h_trkhits_etime_0->Fill(trkhit.etime[0]);
          h_trkhits_etime_1->Fill(trkhit.etime[1]);
          h_trkhits_tot_0->Fill(trkhit.tot[0]);
          h_trkhits_tot_1->Fill(trkhit.tot[1]);
          h_trkhits_ptoca->Fill(trkhit.ptoca);
          h_trkhits_stoca->Fill(trkhit.stoca);
          h_trkhits_rdoca->Fill(trkhit.rdoca);
          h_trkhits_rdocavar->Fill(trkhit.rdocavar);
          h_trkhits_rdt->Fill(trkhit.rdt);
          h_trkhits_rtocavar->Fill(trkhit.rtocavar);
          h_trkhits_udoca->Fill(trkhit.udoca);
          h_trkhits_udocavar->Fill(trkhit.udocavar);
          h_trkhits_udt->Fill(trkhit.udt);
          h_trkhits_utocavar->Fill(trkhit.utocavar);
          h_trkhits_rupos->Fill(trkhit.rupos);
          h_trkhits_uupos->Fill(trkhit.uupos);
          h_trkhits_rdrift->Fill(trkhit.rdrift);
          h_trkhits_cdrift->Fill(trkhit.cdrift);
          h_trkhits_sderr->Fill(trkhit.sderr);
          h_trkhits_uderr->Fill(trkhit.uderr);
          h_trkhits_dvel->Fill(trkhit.dvel);
          h_trkhits_lang->Fill(trkhit.lang);
          h_trkhits_utresid->Fill(trkhit.utresid);
          h_trkhits_utresidmvar->Fill(trkhit.utresidmvar);
          h_trkhits_utresidpvar->Fill(trkhit.utresidpvar);
          h_trkhits_udresid->Fill(trkhit.udresid);
          h_trkhits_udresidmvar->Fill(trkhit.udresidmvar);
          h_trkhits_udresidpvar->Fill(trkhit.udresidpvar);
          h_trkhits_rtresid->Fill(trkhit.rtresid);
          h_trkhits_rtresidmvar->Fill(trkhit.rtresidmvar);
          h_trkhits_rtresidpvar->Fill(trkhit.rtresidpvar);
          h_trkhits_rdresid->Fill(trkhit.rdresid);
          h_trkhits_rdresidmvar->Fill(trkhit.rdresidmvar);
          h_trkhits_rdresidpvar->Fill(trkhit.rdresidpvar);
          h_trkhits_wdot->Fill(trkhit.wdot);
          h_trkhits_poca_x->Fill(trkhit.poca.x());
          h_trkhits_poca_y->Fill(trkhit.poca.y());
          h_trkhits_poca_z->Fill(trkhit.poca.z());
          h_trkhits_uwirephi->Fill(trkhit.uwirephi);
          h_trkhits_ustrawdist->Fill(trkhit.ustrawdist);
          h_trkhits_ustrawphi->Fill(trkhit.ustrawphi);
          h_trkhits_dhit->Fill(trkhit.dhit);
          h_trkhits_dactive->Fill(trkhit.dactive);
        }
      }
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
