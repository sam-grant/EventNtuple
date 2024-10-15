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


## Classes
There are various classes that combine together branches at different dimensions

| Class | Single Objects | Vectors | Vector-of-Vectors |
|-----|-----|----|-----|
| Event | ```evtinfo```, ```evtinfomc``` | ```trk``` | ```trksegs``` |
| Track | ```trk``` | ```trksegs``` | none |
| TrackSegment | ```trkseg``` | none | none |

## Supported Branches
The currently supported branches are:
* evtinfo, evtinfomc
* trk
* trksegs

## Cut Functions

### Common Cut Functions

Here are the common cut functions defined in ```EventNtuple/utils/rooutil/inc/common_cuts.hh``` with explanations:

| function | cuts on | result |
|----|----|----|
|```is_e_minus``` | tracks | true if e-minus hypothesis |
|```is_e_plus``` | tracks | true if e-plus hypothesis |
|```is_mu_minus``` | tracks | true if mu-minus hypothesis |
|```is_mu_plus``` | tracks | true if mu-plus hypothesis |
|```tracker_entrance``` | track segments | true if track segment is at tracker entrance |
|```tracker_middle``` | track segments | true if track segment is at tracker middle |
|```tracker_exit``` | track segments | true if track segment is at tracker exit |

### Combining Cut Functions

There are two ways to combine cut functions:

1. Write a new one yourself e.g:

```
bool my_cut(onst Track& track) {
   return good_track(track) && is_e_minus(track);
}
...
int n_e_minus_good_tracks = event.CountTracks(my_cut);
```

2. or, be combine them in a [lambda function](https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170) (similar to python):

```
int n_e_minus_good_tracks = event.CountTracks([](const Track& track){ return is_e_minus(track) && good_track(track); });
```

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
5. If appropriate, add branches to other classes (e.g. Track.hh) and to ```Event::Update()```
