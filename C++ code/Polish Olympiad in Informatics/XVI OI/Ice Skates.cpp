#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct SegTree
{
	LL LMX[200000*4],RMX[200000*4],MMX[200000*4],SUM[200000*4];
	void Maintain(const int id)
	{
		LMX[id]=max(LMX[id*2],SUM[id*2]+LMX[id*2+1]);
		RMX[id]=max(RMX[id*2]+SUM[id*2+1],RMX[id*2+1]);
		MMX[id]=max(RMX[id*2]+LMX[id*2+1],max(MMX[id*2],MMX[id*2+1]));
		SUM[id]=SUM[id*2]+SUM[id*2+1];
	}
	void Build(const int id,const int l,const int r,const int K)
	{
		if(l==r)
		{
			SUM[id]=-K;
			LMX[id]=RMX[id]=MMX[id]=max(0LL,SUM[id]);
			return;
		}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,K),Build(id*2+1,mid+1,r,K);
		Maintain(id);
	}
	void Add(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			SUM[id]+=val;
			LMX[id]=RMX[id]=MMX[id]=max(0LL,SUM[id]);
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Add(id*2,l,mid,loc,val);
		else Add(id*2+1,mid+1,r,loc,val);
		Maintain(id);
	}
}SEG;
int N,M,K,D;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&K,&D)==4)
	{
		SEG.Build(1,1,N,K);
		for(int i=0;i<D;i++)SEG.Add(1,1,N,N-i,K);
		for(int i=0,r,x;i<M;i++)
		{
			scanf("%d%d",&r,&x);
			SEG.Add(1,1,N,r,x);
			puts(SEG.MMX[1]<=(LL)D*K?"TAK":"NIE");
		}
	}
	return 0;
}
