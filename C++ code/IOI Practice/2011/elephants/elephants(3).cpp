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
		for(int i=1;i<SZ;i++)assert(X[ID[i-1]]<=X[ID[i]]);
		if(SZ>MAX_SZ)SplitMe();
		assert(LeftBound()<=X[ID.front()]&&X[ID.back()]<=RigtBound());
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
			else CAMERA[i]=make_pair(CAMERA[j+1].first+1,CAMERA[j+1].second);
		}
		SAVED=true;
	}
	void Solve(int &ans,int &loc)
	{
		if(ID.empty())return;
		if(!SAVED)Rebuild();
		assert(SAVED);
		assert(SZ==(int)ID.size());
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
	int LeftBound()
	{
		while(LEFT&&LEFT->ID.empty())
		{
			Bucket *nxt_left=LEFT->LEFT;
			delete LEFT;
			LEFT=nxt_left;
			if(LEFT)LEFT->RIGT=this;
		}
		if(!LEFT)return -1;
		return X[LEFT->ID.back()];
	}
	int RigtBound()
	{
		while(RIGT&&RIGT->ID.empty())
		{
			Bucket *nxt_rigt=RIGT->RIGT;
			delete RIGT;
			RIGT=nxt_rigt;
			if(RIGT)RIGT->LEFT=this;
		}
		if(!RIGT)return 1000000001;
		return X[RIGT->ID.front()];
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
void Check()
{
	int loc=-1;
	for(Bucket *cur=BEGIN;cur;cur=cur->RIGT)
	{
		for(const int id:cur->ID)assert(loc<=X[id]),loc=X[id];
	}
}
void init(int _N, int _L, int _X[])
{
//	sort(_X,_X+_N);
	N=_N,L=_L;
	for(int i=0;i<N;i++)X[i]=_X[i],BUCKET[i]=NULL;
	for(int i=1;i<N;i++)assert(X[i-1]<=X[i]);
	BEGIN=new Bucket();
	Bucket *cur=BEGIN;
	for(int i=0;i<N;i++)
	{
		cur->Insert(i);
		if(cur->RIGT)cur=cur->RIGT;
	}
	Check();
	for(int i=0;i<N;i++)assert(BUCKET[i]!=NULL);
}
int update(int id, int y)
{
	assert(0<=id&&id<N&&0<=y&&y<=1000000000);
//	Print();
//	printf("id=%d\n",id);
//	puts("a");
	BUCKET[id]->Erase(id);
//	puts("b");
	Bucket *cur=BEGIN;
	X[id]=y;
	for(;;cur=cur->RIGT)
	{
		assert(cur);
//		printf("(%d,%d)\n",cur->LeftBound(),cur->RigtBound());
//		assert(cur->LeftBound()<=cur->RigtBound());
		if(cur->LeftBound()<=y&&y<cur->RigtBound())
		{
			cur->Insert(id);
			break;
		}
	}
	return Solve();
}
