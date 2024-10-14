root -l -b -q utils/rooutil/examples/PrintEvents.C++\(\"nts.ntuple.mock.root\",true\)
root -l -b -q utils/rooutil/examples/PlotEntranceMomentum.C++\(\"nts.ntuple.mock.root\"\)
root -l -b -q utils/rooutil/examples/CreateTree.C++\(\"nts.ntuple.mock.root\"\)
root -l -b -q utils/rooutil/examples/TimingTest.C++\(\"nts.ntuple.mock.root\"\)

root -l -b -q utils/rooutil/examples/PrintEvents.C++\(\"nts.ntuple.mockNoMC.root\",false\)
root -l -b -q utils/rooutil/examples/PlotEntranceMomentum.C++\(\"nts.ntuple.mockNoMC.root\"\)
root -l -b -q utils/rooutil/examples/CreateTree.C++\(\"nts.ntuple.mockNoMC.root\"\)
root -l -b -q utils/rooutil/examples/TimingTest.C++\(\"nts.ntuple.mockNoMC.root\"\)

root -l -b -q validation/create_val_file_rooutil.C++\(\"nts.ntuple.mock.root\",\"val.ntuple.rooutil.root\"\)
