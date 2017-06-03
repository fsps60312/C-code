#include<cstdio>
#include<cassert>
#include<algorithm>
//#define int long long
using namespace std;
typedef long long LL;
const int INF=2147483647;
bool TooLarge(const LL n,const int road,const int bound)
{
//	printf("(n=%lld,road=%lld,bound=%lld)\n",n,road,bound);
	if(n-1LL>road)return true;
	LL r=road-(n-1LL);
	int now=n-1;
//	if(now<=bound)return false;
	for(LL i=1LL;r>0LL;i++)
	{
		r-=i;
		if(i==1LL)now-=2;
		else --now;
		if(now<=bound)return false;
	}
	return now>bound;
}
int K,N,R,S[100001];
LL SUM[100001];
LL GetMN()
{
	LL l=2LL,r=1e5;
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(mid*(mid-1LL)/2>=R)r=mid;
		else l=mid+1LL;
	}
	return r;
}
LL GetMX(const int bound)
{
	LL l=GetMN(),r=R+1;
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(TooLarge(mid,R,bound))r=mid-1;
		else l=mid;
	}
	return r;
}
struct SemTree
{
	int S[400000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build((id<<1),l,mid),Build((id<<1)+1,mid+1,r);
		}
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return S[id];
		const int mid=(l+r)/2;
		return min(Query((id<<1),l,mid,bl,br),Query((id<<1)+1,mid+1,r,bl,br));
	}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r){S[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify((id<<1),l,mid,loc,val);
		else Modify((id<<1)+1,mid+1,r,loc,val);
		S[id]=min(S[(id<<1)],S[(id<<1)+1]);
	}
}SEM;
LL Solvable(const int mx)
{
	const LL mn=GetMN();
//	printf("(%lld,%lld)\n",mn,mx);
	static int dp[100001];
	for(int i=0;i<=N;i++)dp[i]=INF;
	SEM.Build(1,0,N);
	dp[0]=0,SEM.Modify(1,0,N,0,dp[0]);
	for(int i=1;i<=N;i++)
	{
		const int l=lower_bound(SUM,SUM+N+1,SUM[i]-mx)-SUM;
		const int r=upper_bound(SUM,SUM+N+1,SUM[i]-mn)-SUM-1;
		if(l>r)continue;
		dp[i]=SEM.Query(1,0,N,l,r);
		if(dp[i]!=INF)
		{
			++dp[i];
			SEM.Modify(1,0,N,i,dp[i]);
		}
	}
//	printf("dp[%lld]=%lld\n",N,dp[N]);
	return dp[N];
}
struct SegTree
{
	int S[400000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=-INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id<<1,l,mid),Build((id<<1)+1,mid+1,r);
		}
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return S[id];
		const int mid=(l+r)/2;
		return max(Query((id<<1),l,mid,bl,br),Query((id<<1)+1,mid+1,r,bl,br));
	}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r){S[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify((id<<1),l,mid,loc,val);
		else Modify((id<<1)+1,mid+1,r,loc,val);
		S[id]=max(S[(id<<1)],S[(id<<1)+1]);
	}
}SEG;
bool Solvable()
{
	const LL mn=GetMN(),mx=R+1;
//	printf("(%lld,%lld)\n",mn,mx);
	static int dp[100001];
	for(int i=0;i<=N;i++)dp[i]=-INF;
	SEG.Build(1,0,N);
	dp[0]=0,SEG.Modify(1,0,N,0,dp[0]);
	for(int i=1;i<=N;i++)
	{
		const int l=lower_bound(SUM,SUM+N+1,SUM[i]-mx)-SUM;
		const int r=upper_bound(SUM,SUM+N+1,SUM[i]-mn)-SUM-1;
		if(l>r)continue;
		dp[i]=SEG.Query(1,0,N,l,r);
		if(dp[i]!=-INF)
		{
			++dp[i];
			SEG.Modify(1,0,N,i,dp[i]);
		}
	}
//	printf("dp[%lld]=%lld\n",N,dp[N]);
	return dp[N]>=K;
}
bool Solve(const int critical)
{
	return Solvable(GetMX(critical))<=K;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&K,&N,&R)==3)
	{
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),SUM[i]=SUM[i-1]+S[i];
		int l=0,r=R+1;
		if(Solvable())
		{
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(Solve(mid))r=mid;
				else l=mid+1;
			}
		}
		else l=r=R+1;
		if(r==R+1)puts("No Solution");
		else printf("%d\n",r);
	}
	return 0;
}
