# Notes for Developers

This page contains some miscellanous notes for developers

On this page:

* [Structure of the Code](#Structure-of-the-Code)
* [Adding a branch to EventNtuple](#Adding-a-branch-to-EventNtuple)

## Structure of the Code
The code is structured in the following way:

* ```src/EventNtupleMaker_module.cc`` contains the art analyzer module that creates the ```TTree```
* ```inc/*Info*.hh``` contain C++-style ```structs``` which correspond to a branch with the struct members being the leaves. We call these InfoStructs
* ```src/InfoStructHelper.cc``` contain helper functions that take an Offline data product and an InfoStruct and fills the members of the InfoStruct with information from the Offline data product

## Adding a branch to EventNtuple
### Things to think about:
* will the branch contain a single object, an array of objects, or an array of array of objects

### Changes to make to the code:

1. Create a new struct in ```inc/``` (or identify one that can be re-used)
   * make sure to add a comment line like ```// NameOfStruct: description``` for [```ntuplehelper```(./ntuplehelper.md) compatibility
   * also make sure to add a description for every leaf as an in-line comment for [```ntuplehelper```](./ntuplehelper.md) compatibility
   * all leaves should be initialized to default values
   * there should be a ```reset()``` function
2. Add fill functions to either ```InfoStructHelper``` or ```InfoMCStructHelper``` depending on whether these are reco or MC data products
   * make sure to pass by reference
3. In ```src/EventNtuple_module.cc```:
   * add a ```#include``` to your new InfoStruct (if applicable)
   * in ```struct Config``` add a ```fhicl::Atom<art::InputTag>``` for the
   * in the ```private:``` block, add
      * an ```art::InputTag``` for the collection name
      * an ```art::Handle<DataProduct>``` for the collection
      * an ```InfoStruct``` (or ```std::vector<InfoStruct```) to hold the data for the EventNtuple
   * in the constructor:
      * get the tags from the input in the initializer list
      * fill in empty InfoStructs
   * in ```beginJob()``` create the branch
      * make sure to add a ```.``` to the end of the branch name so that the leaves can be accessed with ROOT
   * in ```analyze()```:
      * at the start, reset your InfoStructs so that data is not left in them from previous events
      * get the data product from the event using the ```art::InputTag```
      * fill in your InfoStructs with the ```_infoStructHelper```
4. In ```src/classes.h``` add your new InfoStruct header file
5. In ```src/classes_def.xml``` add your InfoStruct and vector<InfoStruct> etc. if applicable
6. In ```fcl/prolog.fcl``` add your new input tag fhicl parameter
7. Compile and test:

```
muse build -j4 --mu2eCompactPrint
mu2e -c ...
```

8. Add to validation and RooUtil
