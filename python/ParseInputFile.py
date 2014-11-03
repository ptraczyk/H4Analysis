import re
from os import popen
def ParseInputFile(fileName):
	f=open(fileName,"r");
	R={}
	R['config']={}
	for line in f:
		l3=line.split('\n')[0] ## remove \n, spaces ...
		l2=l3.split('#')[0]
		parts=l2.split('=');
		#INCLUDE
		if parts[0] == 'include':
			print "including File:",parts[1]
			K=ParseInputFile(parts[1])
			#copy and update
			for key in K:
				R[key]=K[key];
		#VALUES
		if parts[0] == 'OutputFile':
			R[ parts[0] ] = parts[1]
		#VECTORS
		if parts[0] == 'HV' or \
			parts[0] == 'InputFiles' or  \
			parts[0] == 'Analysis' :
			R[parts[0]]='='.join(parts[1:]).split(',');
		#TABLES
		if parts[0] == 'ENERGIES' or parts[0] == 'PEDESTAL':
			table=parts[1].split(';'); 
			R[parts[0]]=[]
			for row in table:
				R[parts[0]] += row.split(',')
		# FILES
		if parts[0]=='InputBranches' or parts[0] == 'OutputBranches':
			if parts[0] not in R:
				R[parts[0]]=[]
			fileList=parts[1].split(',')
			for fName in fileList:
				fIn=open(fName,"r")
				for branch in fName:
					br= branch.split('#')[0]
					if br == "": continue
					R[parts[0]]+= br
		###CONFIG ANALYSIS
		if parts[0]=='config':
			configline='='.join(parts[1:]).split(' ')
			Analysis=configline[0]
			R[ parts[0] ][ Analysis ]=[]
			for i in range(1,len( configline)):
				#print "Config Line for analysis ", Analysis , " is ",configline[i]
				R[ parts[0] ][ Analysis ].append( configline[i] )
			
	return R
def PrintConfiguration(config):
	print 
	print "===== CONFIGURATION ====="
	for key in config:
		print "key=",key,"has value:",config[key]	
	print "========================="
	print

def chunkIt(seq, num):
  ''' Take a list seq and return a n lists'''
  R=[]
  for i in range(0,num): R.append([])
  for j in range(0,len(seq) ): 
	R[ j%num ].append(seq[j])
  return R
  ### BUG FOR ROUNDING
  ### avg = len(seq) / float(num)
  ### out = []
  ### last = 0.0

  ### while last < len(seq):
  ###   out.append(seq[int(last):int(last + avg)])
  ###   last += avg

  ### return out

def ReadSRM(url):
    prefix=""
    postfix=""
    if "dcap" in url:
	#srmls srm://t3se01.psi.ch:8443/srm/managerv2?SFN=
	#dcap://t3se01.psi.ch:22125/
	##    aosutheou/prefix*postfix
	if '*' in url:
		star=url.rfind('*')
		prefix=url[:star]
		if '/' in prefix:
			slash=prefix.rfind('/')
			prefix=prefix[slash+1:]
		postfix=url[star+1:]
		slash=url.rfind('/')
		url=url[:slash+1]
	
	pfn=re.sub('t3se01.psi.ch:22125','t3se01.psi.ch:8443/srm/managerv2?SFN=', ### T3. TODO Add T2
		re.sub('dcap://','srm://',url)
		)
    elif "srm" in url:
	pfn=url
    else:	
    	pfn=url
    command = "lcg-ls -b -D srmv2 "+pfn+" 2>/dev/null"
    print "Executing command: " + command
    out_pipe = popen( command )
    #print "lcg-ls -l "+pfn+" 2>/dev/null | awk '{print $5}'"
    #out = [ line  for line in out_pipe.readlines() if ( prefix== "" or re.match(prefix,line) ) and ( postfix=="" or re.match(postfix,line) ) ]
    out = [ re.sub('^','dcap://t3se01.psi.ch:22125/',re.sub('\n','',line)) for line in out_pipe.readlines() if  ( postfix== "" or re.search(postfix,line) ) and ( prefix== "" or re.search(prefix,line) )  ]
    #print "OUT IS ",out
    out_pipe.close() 
    return out
	

