#!env python

import os,sys
from optparse import OptionParser

usage = "usage: %prog [options]"
parser=OptionParser(usage=usage)
parser.add_option("","--input" ,dest='input',type='string',help="Input Configuration file",default="")
parser.add_option("","--debug" ,dest='debug',type='int',help="Debug Verbosity. From 0-3. Default=%default",default=0)
(opts,args)=parser.parse_args()


