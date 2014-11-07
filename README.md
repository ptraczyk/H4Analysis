# ReadMe

## Purpose

This framework has been developed in order to work on the output of the unpack, perform the tree-variables calculation that were in the dqm
and extending it with more and more branches, e.g. database info, correction ...

The framework is supposed to run on T3PSI, supporting SRM reading from the t3 se, and t3-batch system.

## Usage

* Compile
>make

* To submit on the batch system
> python python/submit.py -i test/configPhysics.dat -d physics_11_6/ -v 3 -n 100 -q short.q [ --dryrun ]

* To run a dat file
> python python/Loop.py --input test/configPhysics.dat --debug 3


