# RooUtil (draft)

RooUtil is a utility class to help analyze EventNtuple in ROOT-based analysis frameworks. It can be used simply like so:

```
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
void PrintEvents(std::string filename) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;

  // Now loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);
    // Any single-object branch can be accessed with...
    event.branchname->leafname;
  }
}
```

Branches can be directly accessed from this ```event```. However to aid in the complex structure of the ntuple, we also provide helper classes that combine certain branches together.

This is currently under development and the available branches are listed [below](#Supported-Branches)

## ```rooutilhelper```

```rootuilhelper --list-available-cuts``` lists the cuts that are already available in common_cuts.hh

## Classes
There are various classes that combine together branches at different dimensions

| Class | Single Objects | Vectors | Vector-of-Vectors |
|-----|-----|----|-----|
| Event | ```evtinfo```, ```evtinfomc``` | ```trk```, ```trkmc```, ```trkcalohit```, ```trkcalohitmc```, ```trkqual```, ```crvcoincs```, ```crvcoincsmc``` | ```trksegs```, ```trksegmcs```, ```trksegpars_{lh,ch,kl}```, ```trkmcsim```, ```trkhits``` |
| Track | ```trk```, ```trkmc```, ```trkcalohit```, ```trkqual``` | ```trksegs```, ```trksegmcs```, ```trksegpars_{lh,ch,kl}```, ```trkmcsim```, ```trkhits``` | none |
| TrackSegment | ```trkseg```, ```trksegmc```, ```trksegpars_{lh,ch,kl}``` | none | none |
| CrvCoinc | ```crvcoinc```, ```crvcoincmc``` | none | none |
| MCParticle | ```mcsim``` | none | none |
| TrackHit | ```trkhit```, ```trkhitmc``` | none | none |

## Supported Branches
The currently supported branches are:
* evtinfo, evtinfomc
* trk, trkmc
* trksegs, trksegmcs, trksegpars_{lh,ch,kl}
* trkcalohit, trkcalohitmc
* crvcoincs, crvcoincsmc
* trkmcsim
* trkqual
* trkhits, trkhitsmc

## Cut Functions

### Common Cut Functions

There are the common cut functions defined in ```EventNtuple/utils/rooutil/inc/common_cuts.hh```, They can be listed (with explanations) using:

```
rooutilhelper --list-available-cuts
```

### Combining Cut Functions

There are two ways to combine cut functions:

1. Write a new one yourself e.g:

```
// before your main function
bool my_cut(onst Track& track) {
   return good_track(track) && is_e_minus(track);
}
...
// iin your main function's event loop
int n_e_minus_good_tracks = event.CountTracks(my_cut);
```

2. or, you can combine cuts in a [lambda function](https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170) (similar to python):

```
int n_e_minus_good_tracks = event.CountTracks([](const Track& track){ return is_e_minus(track) && good_track(track); });
```

### Adding new cuts
Feel free to add to common_cuts.hh

Some notes on the file:
* We use the following special characters for the cuts to be printed with ```rooutilhelper```:
   * ```//+``` gives the cut section heading
   * ```bool function_name(args) // explanation``` ensures the cut name has an explanation printed too

## Possible Speed Optimizations
By default, RooUtil will read all the branches for every entry. If you are finding that this is too slow, then you can explicity turn on only the branches that you want reading. This can increase the speed by as much as a factor of 10.

```
RooUtil util(filename);
util.TurnOffAllBranches(); // first turn all branches off
util.TurnOnBranches(std::vector<std::string>{"branch1", "branch2"});
```

## For Developers
### Adding a new branch
Checklist:

1. In [Event.hh](inc/Event.hh) add the pointers at the bottom of the file
2. In [Event.hh](inc/Event.hh) constructor, set the branch address
  - make sure to test for existence if the branch may not exist (e.g. it is an MC branch)
3. In [Event.hh](inc/Event.hh) add the #include to the underlying object
4. Add to validation places:
  - [PrintEvents.C](examples/PrintEvents.C): at least the first and last leaf in the struct
  - [create_val_file_rooutil.C](../../validation/create_val_file_rooutil.C)
     - copy contents of struct into place where histograms are defined
     - then copy and replace "type " with "TH1F* h_branchname_" (e.g. "float " with "TH1F* h_trkcalohit_")
     - then copy in " = new TH1F("h_branchname_", "", 100,0,100); //"
     - delete line after "//"
     - add in leaf names to histname (and make separate x, y, z histograms for XYZVectorF leaves)
     - copy histogram lines into main loop
     - search and replace "TH1F* " with ""
     - search and replace " = new TH1F("h_" with "->Fill("
     - search and replace "", "", 100,0,100);" with ");"
     - search and replace "(branchname_" with "(branchname."
     - update histogram ranges
5. If appropriate, add branches to other classes (e.g. Track.hh) and to ```Event::Update()```
   - be sure to test it with an example script
6. Add to this documentation
