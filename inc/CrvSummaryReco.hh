#ifndef CrvSummaryReco_hh
#define CrvSummaryReco_hh

// CrvSummaryReco: summary of the CRV information in the event

namespace mu2e
{
  struct CrvSummaryReco
  {
    int totalPEs = -1;
    int nHitCounters = -1;
    CrvSummaryReco(){}
    CrvSummaryReco(int totalPEs, int nHitCounters) :
      totalPEs(totalPEs),
      nHitCounters(nHitCounters)
    {}
  };
}
#endif


