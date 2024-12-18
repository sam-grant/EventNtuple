filename="\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\""

root -l -b -q utils/rooutil/examples/PrintEvents.C++\(${filename},true\) # special script that takes an additional argument

scripts=( "CreateNtuple.C" "CreateTree.C" "PlotCRVPEs.C" "PlotCRVPEsVsMCEDep.C" "PlotEntranceFitPars.C" "PlotEntranceMomentum.C"
          "PlotEntranceMomentumCRVCut.C" "PlotEntranceMomentumResolution.C" "PlotEntranceMomentumResolution_TrkQualCut.C"
          "PlotMCParentPosZ.C" "PlotMCParticleMom.C" "PlotMuonPosZ.C" "PlotStoppingTargetFoilSegment.C" "PlotTrackNHits_RecoVsTrue.C"
          "PlotTrkCaloHitEnergy.C" "PrintEventsNoMC.C" "TrackCounting.C")

for script in "${scripts[@]}"
do
    root -l -b -q utils/rooutil/examples/${script}++\(${filename}\)

    if [ $? != 0 ]; then # quit as soon as one script fails
        break;
    fi
done

#root -l -b -q utils/rooutil/examples/PrintEvents.C++\(\"/pnfs/mu2e/tape/phy-nts/nts/mu2e/CosmicCORSIKASignalAllOnSpillTriggered/MDC2020ae_perfect_v1_3_v06_00_00f/root/8f/70/nts.mu2e.CosmicCORSIKASignalAllOnSpillTriggered.MDC2020ae_perfect_v1_3_v06_00_00f.001202_00000000.root\",true\)
#root -l utils/rooutil/examples/PlotEntranceMomentum.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
# root -l -b -q utils/rooutil/examples/CreateTree.C++\(\"nts.ntuple.mock.root\"\)
#root -l -b -q utils/rooutil/examples/TimingTest.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
# root -l -b -q utils/rooutil/examples/PlotEntranceMomentumResolution.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
# root -l utils/rooutil/examples/PlotEntranceMomentumResolution_TrkQualCut.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotEntranceMomentumResolution_ManyTrkQualCut.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)

# root -l -b -q utils/rooutil/examples/PlotTrkCaloHitEnergy.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
# root -l -b -q utils/rooutil/examples/PlotCRVPEs.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
# root -l utils/rooutil/examples/PlotEntranceMomentumCRVCut.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotCRVPEsVsMCEDep.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotStoppingTargetFoilSegments.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotMuonPosZ.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotMCParticleMom.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotMCParentPosZ.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotEntranceFitPars.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)
#root -l utils/rooutil/examples/PlotTrackHitTimes.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\"\)

#root -l -b -q utils/rooutil/examples/SimCheck.C++\(\"/pnfs/mu2e/tape/phy-nts/nts/mu2e/ensembleMDS1aOnSpillTriggered/MDC2020ai_perfect_v1_3/root/1e/7e/nts.mu2e.ensembleMDS1aOnSpillTriggered.MDC2020ai_perfect_v1_3.0.root\",true\)
# root -l -b -q utils/rooutil/examples/PrintEvents.C++\(\"nts.ntuple.mockNoMC.root\",false\)
# root -l -b -q utils/rooutil/examples/PlotEntranceMomentum.C++\(\"nts.ntuple.mockNoMC.root\"\)
# root -l -b -q utils/rooutil/examples/CreateTree.C++\(\"nts.ntuple.mockNoMC.root\"\)
# root -l -b -q utils/rooutil/examples/TimingTest.C++\(\"nts.ntuple.mockNoMC.root\"\)

#root -l -b -q validation/create_val_file_rooutil.C++\(\"/pnfs/mu2e/tape/phy-nts/nts/mu2e/CosmicCORSIKASignalAllOnSpillTriggered/MDC2020ae_perfect_v1_3_v06_00_00f/root/8f/70/nts.mu2e.CosmicCORSIKASignalAllOnSpillTriggered.MDC2020ae_perfect_v1_3_v06_00_00f.001202_00000000.root\",\"val.ntuple.rooutil.root\"\)

#root -l -b -q validation/create_val_file_rooutil.C++\(\"../data/nts.mu2e.MDS1f.MDC2020ai_perfect_v1_3.root\",\"val.ntuple.rooutil.root\"\)

#root -l -b -q validation/create_val_file.C\(\"/pnfs/mu2e/tape/phy-nts/nts/mu2e/CosmicCORSIKASignalAllOnSpillTriggered/MDC2020ae_perfect_v1_3_v06_00_00f/root/8f/70/nts.mu2e.CosmicCORSIKASignalAllOnSpillTriggered.MDC2020ae_perfect_v1_3_v06_00_00f.001202_00000000.root\",\"val.ntuple.rooutil.root\"\)
