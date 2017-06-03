#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
struct SegTree
{
	int SZ[400000],N,*A,*V,CUR;
	LL SUM[400000];
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
LL Query(const SegTree &ls,const SegTree &rs,const int id,const int l,const int r,int &sz)
{
	if(sz==0)return 0LL;
	if(rs.SZ[id]-ls.SZ[id]<=sz){sz-=rs.SZ[id]-ls.SZ[id];return rs.SUM[id]-ls.SUM[id];}
	if(l==r){const LL ans=(rs.SUM[id]-ls.SUM[id])/(rs.SZ[id]-ls.SZ[id])*sz;sz=0;return ans;}
	const int mid=(l+r)/2;
	LL ans=0LL;
	ans+=Query(ls,rs,id*2+1,mid+1,r,sz);
	ans+=Query(ls,rs,id*2,l,mid,sz);
	return ans;
}
SegTree LS,RS;
LL Query(const int l,const int r,int k)
{
	LS.Move(l),RS.Move(r+1);
	return Query(LS,RS,1,0,LS.N-1,k);
}
int N,M,S,D,A[100000],V[100000];
LL Solve(const int l1,const int r1,const int l2,const int r2)
{
	if(l1>r1)return 0LL;
	const int mid1=(l1+r1)/2;
	int mid2=l2;
	LL ans=0LL;
	for(int i=l2;i<=r2;i++)
	{
		const int d=(i-mid1)+min(S-mid1,i-S);
		if(d>=D)break;
		const LL ta=Query(mid1,i,D-d);
		if(ta>ans)ans=ta,mid2=i;
	}
	getmax(ans,Solve(l1,mid1-1,l2,mid2));
	getmax(ans,Solve(mid1+1,r1,mid2,r2));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&S,&D)==3)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]),V[i]=A[i];
		sort(V,V+N),M=unique(V,V+N)-V;
		for(int i=0;i<N;i++)A[i]=lower_bound(V,V+M,A[i])-V;
		LS.Build(M,A,V),RS.Build(M,A,V);
		printf("%lld\n",Solve(0,S,S,N-1));
	}
	return 0;
}
