## Single-Object Branches

| branch | explanation |

|--------|-------------|

| evtinfo |   event-level information|
| evtinfomc |   MC-truth event-level information|
| hitcount |   counts of different hit types in an event|
| tcnt |   counts track types and track-related quantities in an event (MARKED FOR REMOVAL)|
| crvsummary |   summary of the CRV information in the event|
| crvsummarymc |   summary of the MC-truth CRV information in the event|

==Vector Branches==
| branch | explanation |
|--------|-------------|
| trk |   information about the reconstructed track|
| trkmc |   MC-truth information about the track|
| trkcalohit |   the calorimeter cluster assigned to a track|
| trkcalohitmc |   MC-truth infromation for calorimeter clusters|
| crvcoincs |   information about a cluster of CRV coincidence triplets|
| crvcoincsmc |   information about the MC track which most likely caused the CRV coincidence triplets|
| crvcoincsmcplane |   information about the point where the MC trajectory crosses the xz plane of CRV-T|
| trkqual |   the output of a multi-variate analysis (MVA)|

==Vector-of-Vector Branches==
| branch | explanation |
|--------|-------------|
| trksegs |   track fit results at particular surfaces|
| trksegpars_lh |   LoopHelix track parameters at each trkseg surface (used for looping tracks)|
| trksegpars_ch |   CentralHelix track parameters at each trkseg surface (used for field-on cosmic tracks)|
| trksegpars_kl |   KinematicLine track parameters for each trkseg surface (used for field-off cosmics)|
| trkmcsim |   information about SimParticles in genealogy|
| trkhits |   information about the straw hits assigned to a track|
| trkhitsmc |   MC-truth information of straw hits assigned to a track|
| trkmats |   information on the straw materials used in the Kalman fit|
| trkmcsci |   information about StepPointMCs|
| trkmcssi |   information that summarizes all StepPointMCs in a given location|
| trksegsmc |   MC-truth information of the SurfaceSteps taken by a particle through passive elements, or virtual detectors|
