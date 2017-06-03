#include "grader.h"
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,L,X[150000];
struct Bucket;
Bucket *BUCKET[150000];
const int MIN_SZ=400,MAX_SZ=800; 
struct Bucket
{
	Bucket *LEFT,*RIGT;
	int SZ;
	vector<int>ID;
	vector<pair<int,int> >CAMERA;
	bool SAVED;
	Bucket():LEFT(NULL),RIGT(NULL),SZ(0),SAVED(false){}
	void Erase(const int id)
	{
		for(int i=0;;i++)
		{
			assert(i<SZ);
			if(ID[i]==id)
			{
				ID.erase(ID.begin()+i),BUCKET[id]=NULL;
				break;
			}
		}
		--SZ;
		SAVED=false;
//		puts("a");
		if(LEFT!=NULL&&LEFT->SZ+SZ<=MIN_SZ)LEFT->MergeMe();
		else if(RIGT!=NULL&&SZ+RIGT->SZ<=MIN_SZ)MergeMe();
//		puts("b");
	}
	void MergeMe()
	{
		assert(RIGT!=NULL);
		for(int i=0;i<RIGT->SZ;i++)ID.push_back(RIGT->ID[i]),BUCKET[RIGT->ID[i]]=this;
		SZ+=RIGT->SZ;
		Bucket *nxt_rigt=RIGT->RIGT;
		delete RIGT;
		RIGT=nxt_rigt;
		if(RIGT)RIGT->LEFT=this;
		SAVED=false;
	}
	void SplitMe()
	{
		const int mid=SZ/2;
		Bucket *rb=new Bucket();
		if(RIGT)RIGT->LEFT=rb;
		rb->RIGT=RIGT;
		RIGT=rb;
		rb->LEFT=this;
		for(int i=mid;i<SZ;i++)rb->ID.push_back(ID[i]),BUCKET[ID[i]]=rb;
		for(int i=mid;i<SZ;i++)ID.pop_back();
		rb->SZ=SZ-mid,SZ=mid;
		SAVED=false;
	}
	void Insert(const int id)
	{
		++SZ;
		BUCKET[id]=this;
		ID.push_back(id);
		for(int i=SZ-2;i>=0&&X[ID[i]]>X[ID[i+1]];i--)swap(ID[i],ID[i+1]);
//		for(int i=1;i<SZ;i++)assert(X[ID[i-1]]<=X[ID[i]]);
		if(SZ>MAX_SZ)SplitMe();
		SAVED=false;
	}
	void Rebuild()
	{
		assert((int)ID.size()==SZ);
		CAMERA.resize(ID.size());
		for(int i=SZ-1,j=SZ-1;i>=0;i--)
		{
			while(X[ID[i]]+L<X[ID[j]])--j;
			if(j==SZ-1)CAMERA[i]=make_pair(1,X[ID[i]]+L);
			else CAMERA[i]=make_pair(CAMERA[j+1].first+1,CAMERA[j].second);
		}
		SAVED=true;
	}
	void Solve(int &ans,int &loc)
	{
		if(!SAVED)Rebuild();
		assert(SAVED);
		if(loc<X[ID.front()])ans+=CAMERA[0].first,loc=CAMERA[0].second;
		else if(loc>=X[ID.back()])return;
		else
		{
			int l=0,r=SZ-1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(X[ID[mid]]<=loc)l=mid+1;
				else r=mid;
			}
			ans+=CAMERA[r].first,loc=CAMERA[r].second;
		}
	}
};
Bucket *BEGIN;
int Solve()
{
	Bucket *cur=BEGIN;
	int ans=0,loc=-1;
	for(;cur;cur=cur->RIGT)cur->Solve(ans,loc);
	return ans;
}
void init(int _N, int _L, int _X[])
{
	N=_N,L=_L;
	for(int i=0;i<N;i++)X[i]=_X[i],BUCKET[i]=NULL;
	BEGIN=new Bucket();
	Bucket *cur=BEGIN;
	for(int i=0;i<N;i++)
	{
		cur->Insert(i);
		if(cur->RIGT)cur=cur->RIGT;
	}
	for(int i=0;i<N;i++)assert(BUCKET[i]!=NULL);
}
int update(int id, int y)
{
	assert(0<=id&&id<N);
//	Print();
//	printf("id=%d\n",id);
//	puts("a");
	BUCKET[id]->Erase(id);
//	puts("b");
	Bucket *cur=BEGIN;
	X[id]=y;
	for(;;cur=cur->RIGT)if((!cur->RIGT||y<X[cur->RIGT->ID.front()]))
	{
		cur->Insert(id);
		break;
	}
	return Solve();
}
