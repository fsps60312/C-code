#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct SzTree
{
	int sz[400000];
	void Build(const int id,const int l,const int r)
	{
		if(l==r){sz[id]=2;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		sz[id]=sz[id*2]+sz[id*2+1];
	}
	int Query(const int id,const int l,const int r,const bool is_left,const int rank)
	{
//		printf("%d(l=%d,r=%d)\n",is_left,l,r);
		assert(rank>=0&&rank<sz[id]);
		if(is_left&&rank==0)return l;
		if(!is_left&&rank==sz[id]-1)return r;
		const int mid=(l+r)/2;
		if(rank<sz[id*2])return Query(id*2,l,mid,is_left,rank);
		else return Query(id*2+1,mid+1,r,is_left,rank-sz[id*2]);
	}
	void Merge(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			sz[id]=0;
			if(l==bl)sz[id]++;
			if(r==br)sz[id]++;
			return;
		}
		const int mid=(l+r)/2;
		Merge(id*2,l,mid,bl,br),Merge(id*2+1,mid+1,r,bl,br);
		sz[id]=sz[id*2]+sz[id*2+1];
	}
}SZTREE;
struct Segment
{
	int l,r;
	Segment(){}
	Segment(const int _l,const int _r):l(_l),r(_r){}
};
vector<Segment>SEGMENT;
int N,C,R,S[99999];
int main()
{
	freopen("in.txt","r",stdin);
	scanf(3,"%d%d%d",&N,&C,&R);
	for(int i=0;i+1<N;i++)scanf(1,"%d",&S[i]);
	SZTREE.Build(1,0,N-1);
	SEGMENT.clear();
	for(int i=0,s,e;i<C;i++)
	{
		scanf(2,"%d%d",&s,&e);
		const int l=SZTREE.Query(1,0,N-1,true,s*2),r=SZTREE.Query(1,0,N-1,false,e*2+1);
//		printf("(%d,%d)\n",l,r);
		SEGMENT.push_back(Segment(l,r));
		SZTREE.Merge(1,0,N-1,l,r);
	}
	return 0;
}
