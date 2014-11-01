def ParseInputFile(fileName):
	f=open(fileName,"r");
	R={}
	for line in f:
		l2=line.split('#')[0]
		parts=l2.split('=');
		#VALUES
		if parts[0] == 'OutputFile':
			R[ parts[0] ] = parts[1]
		#VECTORS
		if parts[0] == 'HV' or
			parts[0] == 'InputFiles' or 
			parts[0] == 'Analysis' :
			R[parts[0]]=parts[1].split(',');	
		#TABLES
		if parts[0] == 'ENERGIES' or parts[0] == 'PEDESTAL':
			table=parts[1].split(';'); 
			R[parts[0]]=[]
			for row in table:
				R += row.split(',')
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
			
	return R
def PrintConfiguration(config):
	print 
	print "===== CONFIGURATION ====="
	for key in config:
		print "key=",key,"has value:",config[key]	
	print "========================="
	print
