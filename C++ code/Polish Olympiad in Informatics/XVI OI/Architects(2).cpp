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
const int MXN=1000000,INF=2147483647;
struct SegTree
{
	int MN[4000000],SZ;
	void Build(const int id,const int l,const int r)
	{
		MN[id]=INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(){SZ=0,Build(1,0,MXN-1);}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r){assert(r==loc);MN[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,val);
		else Modify(id*2+1,mid+1,r,loc,val);
		MN[id]=min(MN[id*2],MN[id*2+1]);
	}
	void Modify(const int loc,const int val){Modify(1,0,MXN-1,loc,val);}
	void PushBack(const int val){Modify(SZ++,val);}
	void PopBack(){Modify(--SZ,INF);}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return MN[id];
		const int mid=(l+r)/2;
		return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
	int Query(const int bl,const int br){return Query(1,0,MXN-1,bl,br);}
}SEQ;
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
int GetNext(const int K,int &remain)
{
	static int last_val=INF;
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
	SEQ.Build();
	for(int v,remain;(v=GetNext(K,remain));)
	{
		while(SEQ.Query(K-1-remain,K-1)<v)SEQ.PopBack();
		if(SEQ.SZ<K)SEQ.PushBack(v);
	}
	assert(SEQ.SZ==K);
	for(int i=0;i<K;i++)wypisz(SEQ.Query(i,i));
	return 0;
}
