#ifndef LOOP_AND_FILL_H
#define LOOP_AND_FILL_H

#include "interface/Looper.hpp"
#include "interface/Filler.hpp"
#include "interface/Histos.hpp"

class LoopAndFill: 
	virtual public Histos,
	virtual public Looper,
	virtual public Filler
{
protected:
	//template<class T> 
	//void CopyArray(T* src,T*dest,int n);
	//template<class T> 
	//void CopyVector(vector<T> *src,vector<T>*dest);
	void CopyArray(bool* src,bool*dest,int n);
	void CopyVector(vector<bool> *src,vector<bool>*dest);
	void CopyArray(int* src,int*dest,int n);
	void CopyVector(vector<int> *src,vector<int>*dest);
	void CopyArray(unsigned int* src,unsigned int*dest,int n);
	void CopyVector(vector<unsigned int> *src,vector<unsigned int>*dest);
	void CopyArray(float* src,float*dest,int n);
	void CopyVector(vector<float> *src,vector<float>*dest);
	void CopyArray(double* src,double*dest,int n);
	void CopyVector(vector<double> *src,vector<double>*dest);
	void CopyArray(unsigned long long* src,unsigned long long*dest,int n);
	void CopyVector(vector<unsigned long long> *src,vector<unsigned long long>*dest);
public:
	LoopAndFill(){};
	~LoopAndFill(){};
	void Init();
	void Close();
	void Fill();
	void Write();
};

 // template<class T> 
 // void CopyArray(T* src,T* dest,int n)
 // 	{
 // 	for(int i=0;i<n;++i) dest[i]=src[i];
 // 	}
 // template<class T> 
 // void CopyVector(vector<T> *src,vector<T> *dest)
 // 	{
 // 	dest->clear();
 // 	for(unsigned int i=0;i<src->size() ;++i)
 // 		dest->push_back( src->at(i) );
 // 	}
#endif
