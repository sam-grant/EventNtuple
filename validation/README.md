## Validation

We want to make sure that any changes we make to the code don't:
* stop fcl files from working, or
* change the content of the EventNtuple unexpectedly

### Validating EventNtuple Runs
From ```EventNtuple/``` directory:

```
. ./validation/test_fcls.sh
```

This script will run all the supported fcl files over relevant datasets. All tests should report ```OK```

### Creating a Validation File
Before making any changes, create an EventNtuple file and run the validation script. This creates a new ROOT file with histograms created from the EventNtuple ntuple:

```
mu2e -c EventNtuple/fcl/from_mcs_mockdata.fcl -S filelist.txt --TFileName nts.ntuple.before.root

root -l -b EventNtuple/validation/create_val_file.C\(\"nts.ntuple.before.root\",\"val.ntuple.before.root\"\)
```

### Validating EventNtuple Contents

Then make your changes, rebuild the code and then re-run:

```
mu2e -c EventNtuple/fcl/EventNtupleReco.fcl -S filelist.txt --TFileName nts.ntuple.after.root

root -l -b EventNtuple/validation/create_val_file.C\(\"nts.ntuple.after.root\",\"val.ntuple.after.root\"\)
```

Finally, to compare the two sets of histograms we use [valCompare](https://mu2ewiki.fnal.gov/wiki/Validation#valCompare)

```
valCompare -p ntuple-validation-booklet.pdf -r val.ntuple.before.root val.ntuple.after.root
```

We should have perfect matches between all histograms. However, in some rare instances, we may expect differences. If you see any non-perfect matches, then discuss with the EventNtuple L4.
