#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
typedef long long LL;
LL K;
struct Ans
{
	LL n,m;
	Ans(){}
	Ans(LL n,LL m):n(n),m(m){}
};
map<LL,Ans>ANS;
Ans solve()
{
	if(ANS.find(K)!=ANS.end())return ANS[K];
//	LL l=1,r=K,mid;
//	while(l<r)
//	{
//		mid=(l+r+1LL)/2;
//		if(mid*mid>=K)r=mid-1LL;
//		else l=mid;
//	}
//	if(l*(l+1LL)==K)return Ans(l+1LL,l-1);
	if(K>1LL)return Ans(K,K-1LL);
	return Ans(-1LL,-1LL);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(LL cnt=12LL;cnt>=3LL;cnt--)
	{
		LL now=1,i;
		for(i=2LL;i<=cnt;i++)now*=i;
		i=1LL;
		for(;now<=1000000000LL;i++,now/=i,now*=(i+cnt-1))
		{
			if(ANS.find(now)!=ANS.end())continue;
			ANS[now]=Ans(i+cnt-1,i);
		}
	}
	while(scanf("%lld",&K)==1)
	{
		Ans ans=solve();
		static int kase=1;
		printf("Case %d: ",kase++);
		if(ans.n==-1LL)puts("Impossible");
		else
		{
//			LL t=1LL;
//			for(LL i=ans.m+1LL;i<=ans.n;i++)t*=i;
//			if(t!=K)assert(0);
			printf("%lld %lld\n",ans.n,ans.m);
		}
	}
	return 0;
}
