#!env python

import os,sys
import array
from optparse import OptionParser

usage = "usage: %prog [options]"
parser=OptionParser(usage=usage)
parser.add_option("","--input" ,dest='input',type='string',help="Input Configuration file",default="")
parser.add_option("","--debug" ,dest='debug',type='int',help="Debug Verbosity. From 0-3. Default=%default",default=0)
(opts,args)=parser.parse_args()


if opts.debug >0 : print "-> Importing ROOOT"

sys.argv=[]
import ROOT 
ROOT.gROOT.SetBatch(1);

if opts.debug >0 : print "-> Importing Analysis Library"

ROOT.gSystem.Load("bin/H4Analysis.so")

if opts.debug >0 : print "-> Parse Configuration"

from  ParseInputFile import *
config=ParseInputFile(opts.input)

if opts.debug>0 : PrintConfiguration(config)


if opts.debug >0 : print "-> Init Class"

l=ROOT.LoopAndFill()

## INPUT
l.chainName="H4tree"
#l.inputBranches[]=1
for f in config['InputFiles']:
	print "Adding file '"+f+"'"
	l.AddToChain(f);
for b in config['InputBranches']:
	l.inputBranches[b]=1
## OUTPUT
l.outFileName=config['OutputFile']
l.outTreeName="outputTree"
for b in config['OutputBranches']:
	l.activeBranches[b]=1
l.Init();

## INIT ANALYSIS
analysis=[]
###  for name in config['Analysis']:
###  	print "Loading Analysis: '" +name+"'"
###  	#exec("A=ROOT."+name)
###  	ROOT.ParseLine("")
###  	A.Init( l);
###  	analysis.append(A)

A=ROOT.PedestalAnalysis()
A.Init(l)
analysis.append(A)

if opts.debug >0 : print "-> Looping"

for iEntry in range(0,l.GetEntries() ) :
	if opts.debug >0  and iEntry % 1000 ==0 : print "--> Entry",iEntry,"of",l.GetEntries()
	l.GetEntry(iEntry)
	## ALL ANALYSIS ANALIZE EVENT
	for A in analysis:
		A.AnalizeEvent()
	
if opts.debug >0 : print "-> Writing"
l.Write();
l.Close();

if opts.debug >0 : print "-> END"
