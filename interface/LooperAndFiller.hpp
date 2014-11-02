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
	template<class T> 
	void CopyArray(T* src,T*dest,int n);
	template<class T> 
	void CopyVector(vector<T> *src,vector<T>*dest);
public:
	LoopAndFill(){};
	~LoopAndFill(){};
	void Init();
	void Close();
	void Fill();
};

template<class T> 
void CopyArray(T* src,T* dest,int n)
	{
	for(int i=0;i<n;++i) dest[i]=src[i];
	}
template<class T> 
void CopyVector(vector<T> *src,vector<T> *dest)
	{
	dest->clear();
	for(unsigned int i=0;i<src->size() ;++i)
		dest->push_back( src->at(i) );
	}
#endif
