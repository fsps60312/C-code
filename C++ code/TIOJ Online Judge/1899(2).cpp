#include"lib1899.h"
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
struct SegTree
{
	int SZ[400000],CUR,N;
	LL SUM[400000];
	int *A,*V;
	void Build(const int id,const int l,const int r)
	{
		SZ[id]=0,SUM[id]=0LL;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N,int *_A,int *_V)
	{
		N=_N,A=_A,V=_V;
		Build(1,0,N-1);
		CUR=0;
	}
	void Modify(const int id,const int l,const int r,const int loc,const int sz,const LL sum)
	{
		assert(l<=loc&&loc<=r);
		SZ[id]+=sz,SUM[id]+=sum;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,sz,sum);
			else Modify(id*2+1,mid+1,r,loc,sz,sum);
		}
	}
	void Move(const int goal)
	{
		for(;CUR<goal;)Modify(1,0,N-1,A[CUR],1,V[A[CUR]]),++CUR;
		for(;CUR>goal;)--CUR,Modify(1,0,N-1,A[CUR],-1,-V[A[CUR]]);
	}
};
LL Query_Ksum(const SegTree &lt,const SegTree &rt,const int id,const int l,const int r,int &sz)
{
	if(sz==0)return 0LL;
	if(rt.SZ[id]-lt.SZ[id]<=sz){sz-=rt.SZ[id]-lt.SZ[id];return rt.SUM[id]-lt.SUM[id];}
	if(l==r){const LL ans=(rt.SUM[id]-lt.SUM[id])/(rt.SZ[id]-lt.SZ[id])*sz;sz=0;return ans;}
	const int mid=(l+r)/2;
	LL ans=Query_Ksum(lt,rt,id*2+1,mid+1,r,sz);
	ans+=Query_Ksum(lt,rt,id*2,l,mid,sz);
	return ans;
}
SegTree LS,RS;
LL Query_Ksum(const int l,const int r,int k)
{
	LS.Move(l),RS.Move(r+1);
	return Query_Ksum(LS,RS,1,0,LS.N-1,k);
}
int D,S;
LL Query(const int l,const int bl,const int br,int &mid)
{
	mid=bl;
	LL ans=0LL;
	for(int i=bl;i<=br;i++)
	{
		const int d=D-((i-l)+min(i-S,S-l));
		if(d<=0)break;
		const LL v=Query_Ksum(l,i,d);
		if(v>ans)mid=i,ans=v;
	}
	return ans;
}
int N,*A;
LL Solve(const int l1,const int r1,const int l2,const int r2)
{
	if(l1>r1)return 0LL;
	const int mid1=(l1+r1)/2;
	int mid2;
	LL ans=Query(mid1,l2,r2,mid2);
	getmax(ans,Solve(l1,mid1-1,l2,mid2));
	getmax(ans,Solve(mid1+1,r1,mid2,r2));
	return ans;
}
int V[100000];
LL findMaxAttraction(int _N,int _S,int _D,int *_A)
{
	N=_N,S=_S,D=_D,A=_A;
	for(int i=0;i<N;i++)V[i]=A[i];
	sort(V,V+N);
	const int m=unique(V,V+N)-V;
	for(int i=0;i<N;i++)A[i]=lower_bound(V,V+m,A[i])-V;
	LS.Build(m,A,V),RS.Build(m,A,V);
	return Solve(0,S,S,N-1);
}
