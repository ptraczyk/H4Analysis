#!env python

import os,sys
from glob import glob

from optparse import OptionParser

usage = "usage: %prog [options]"
parser=OptionParser(usage=usage)
parser.add_option("-i","--input" ,dest='input',type='string',help="Input Configuration file",default="")
parser.add_option("-d","--dir" ,dest='dir',type='string',help="Directory where to write the configuration",default="submit")
parser.add_option("-v","--debug" ,dest='debug',type='int',help="Debug Verbosity. From 0-3. Default=%default",default=0)
(opts,args)=parser.parse_args()



