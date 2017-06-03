#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
pair<int,int>CARD[200000];
struct StType
{
	int l,r,v1,v2;
	StType(){}
	StType(const int _l,const int _r,const int _v1,const int _v2):l(_l),r(_r),v1(_v1),v2(_v2){}
};
struct SegTree
{
	StType S[800000];
	StType Merge(const StType &a,const StType &b)
	{
		assert(b.l-a.r==1);
		StType ans=a;
		ans.r=b.r;
		if(a.v1==1||a.v1==2)
		{
			const int v=(a.v1==1?CARD[a.r].first:CARD[a.r].second);
			if(v<=CARD[b.l].first)ans.v1=b.v1;
			else if(v<=CARD[b.l].second)ans.v1=b.v2;
			else ans.v1=3;
		}
		else assert(ans.v1==3);
		if(a.v2==1||a.v2==2)
		{
			const int v=(a.v2==1?CARD[a.r].first:CARD[a.r].second);
			if(v<=CARD[b.l].first)ans.v2=b.v1;
			else if(v<=CARD[b.l].second)ans.v2=b.v2;
			else ans.v2=3;
		}
		else assert(ans.v2==3);
		return ans;
	}
	void Build(const int id,const int l,const int r)
	{
		if(l==r){S[id]=StType(r,r,1,2);return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		S[id]=Merge(S[id*2],S[id*2+1]);
	}
	void Modify(const int id,const int l,const int r,const int loc,const pair<int,int>&val)
	{
		if(l==r)
		{
			assert(r==loc);
			CARD[r]=val;
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,val);
		else Modify(id*2+1,mid+1,r,loc,val);
		S[id]=Merge(S[id*2],S[id*2+1]);
	}
}SEG;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),CARD[i]=make_pair(min(a,b),max(a,b));
		SEG.Build(1,0,N-1);
		scanf("%d",&M);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			const pair<int,int>c1=CARD[a],c2=CARD[b];
			SEG.Modify(1,0,N-1,a,c2);
			SEG.Modify(1,0,N-1,b,c1);
			puts(SEG.S[1].v1<3?"TAK":"NIE");
		}
	}
	return 0;
}
