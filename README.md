# ReadMe

## Purpose

This framework has been developed in order to work on the output of the unpack, perform the tree-variables calculation that were in the dqm
and extending it with more and more branches, e.g. database info, correction ...

The framework is supposed to run on T3PSI, supporting SRM reading from the t3 se, and t3-batch system.

## Usage

* Compile
>make

* To submit on the batch system
> python python/submit.py -i test/configPhysics.dat -d physics_11_6/ -v 3 -n 100 -q short.q [--dryrun]

* To run a dat file
> python python/Loop.py --input test/configPhysics.dat --debug 3

## DAT Files description
Analysis is configured throw dat files. Keys in the dat files are:
* OutputFile
* chainName: input tree name
* outTreeName
* HV [not used]
* InputFiles: vector
* Analysis: vector, analysis are run in the given order
* config: use to configure an analysis.Public element are called. Exe: config=AnalysisName key1=val1 funct1(par1)
* InputBranches: file containing the list of branches
* OutputBranches: file containing the list of branches
* InputRuns: will change the InputFile key. InputRuns=template%%RUN%% run1,run2..
* include: will include an other input files. each key in that input file is overwritten. for the configuration, each analysis configuration is overwritten.

## Wrote an extra analysis
* Inheriths from BaseAnalysis.
* Implement the methods AnalyzeEvent() and ClearEvents(), they are called at each event.
* A pointer to the loop and Fill structure is present (LoopAndFill *l) 

## Add A branch in the input/output tree
* Add the element to the tree (input/output) in interface/Event.hpp (and if the case modify the cpp)
* Add the Branch Address in the input tree in src/Looper.cpp 
* Add the Branch in the outputfile in src/Filler.cpp
* Add the copy from the input to the output file in src/LooperAndFiller.cpp

