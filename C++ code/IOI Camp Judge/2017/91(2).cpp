#include<cstdio>
#include<cassert>
#include<deque>
#include<cmath>
#include<algorithm>
using namespace std;
#define double long double
typedef long long LL;
int N;
LL K,S[100001],DP[100001];
LL Trans(const int a,const int b)
{
	assert(a<b);
	const LL l=S[b]-S[a];
	return DP[a]+K+l*l*l;
}
bool Judge(const int a,const int b,const int c)
{
	assert(a<b&&b<c);
	auto f=[](const int i,const LL x){const LL l=x-S[i];return DP[i]+l*l*l;};
	LL l=0,r=S[N];
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(f(a,mid)<f(b,mid))l=mid+1;
		else r=mid;
	}
	return f(c,r)<=f(b,r);
}
int main()
{
//	freopen("data.in","r",stdin);
	int testcount=0;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%lld",&N,&K);
		S[0]=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%lld",&S[i]);
			if(S[i]==0)
			{
				--i,--N;
				continue;
			}
			S[i]+=S[i-1];
		}
		DP[0]=0;
		deque<int>deq;
		deq.push_back(0);
		for(int i=1;i<=N;i++)
		{
			while(deq.size()>=2&&Trans(deq[0],i)>=Trans(deq[1],i))deq.pop_front();
			DP[i]=Trans(deq.front(),i);
//			printf("dp[%d]=%lld\n",i,DP[i]);
			while(deq.size()>=2&&Judge(deq[deq.size()-2],deq.back(),i))deq.pop_back();//,puts("b");
			deq.push_back(i);
		}
		printf("%lld\n",max(DP[N],K));
	}
	return 0;
}
