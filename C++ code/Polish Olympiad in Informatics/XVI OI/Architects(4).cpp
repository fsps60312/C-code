//#define SELF
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
#ifndef SELF
#include"carclib.h"
#endif
using namespace std;
#ifdef SELF
int inicjuj(){return 3;}
int wczytaj()
{
	static int ans[]={12,5,8,3,15,8,0},kase=0;
	return ans[kase++];
}
void wypisz(int ans)
{
	printf("ans=%d\n",ans);
}
#endif
struct Heap
{
	int S[1000001],ID[1000001],LOC[1000001],SZ;
	void Clear(){SZ=0;}
	inline void Swap(const int i1,const int i2)
	{
		swap(LOC[ID[i1]],LOC[ID[i2]]);
		swap(ID[i1],ID[i2]);
		swap(S[i1],S[i2]);
	}
	inline int Float(int i)
	{
		for(;i>1&&S[i]<S[i>>1];i>>=1)Swap(i>>1,i);
		return i;
	}
	inline int Sink(int i)
	{
		for(;;)
		{
			if((i<<1)>SZ)return i;
			if((i<<1)+1>SZ)
			{
				if(S[i]<=S[i<<1])return i;
				else
				{
					Swap(i,i<<1);
					return i<<1;
				}
			}
			const int nxt=(S[i<<1]<S[(i<<1)+1]?i<<1:(i<<1)+1);
			if(S[i]<=S[nxt])return i;
			Swap(i,nxt);
			i=nxt;
		}
	}
	inline void Push(const int val,const int id)
	{
		++SZ;
		S[SZ]=val,ID[SZ]=id,LOC[id]=SZ;
		Float(SZ);
	}
	inline void Erase(const int id)
	{
		const int loc=LOC[id];
		Swap(loc,SZ),--SZ;
		if(loc<=SZ)Sink(Float(loc));
	}
	inline int Top()
	{
		return S[1];
	}
}HEAP;
inline int GetNext(const int K,int &remain)
{
	static int last_val=2147483647;
	static queue<int>q;
	while(last_val&&(int)q.size()<K)
	{
		last_val=wczytaj();
		if(last_val)q.push(last_val);
	}
	if(q.empty())return 0;
	const int ans=q.front();q.pop();
	remain=(int)q.size();
	return ans;
}
int main()
{
	const int K=inicjuj();
	static int ANS[1000000],L=0,SZ=0;
	HEAP.Clear();
	for(int v,remain;(v=GetNext(K,remain));)
	{
		if(L+1==K-1-remain)HEAP.Erase(L++);
		while(HEAP.SZ&&HEAP.Top()<v)HEAP.Erase(--SZ);
		if(SZ<K)HEAP.Push(ANS[SZ]=v,SZ),SZ++;
	}
	assert(SZ==K);
	for(int i=0;i<K;i++)wypisz(ANS[i]);
	return 0;
}
