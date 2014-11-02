def ParseInputFile(fileName):
	f=open(fileName,"r");
	R={}
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
			R[parts[0]]=parts[1].split(',');
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
			
	return R
def PrintConfiguration(config):
	print 
	print "===== CONFIGURATION ====="
	for key in config:
		print "key=",key,"has value:",config[key]	
	print "========================="
	print
