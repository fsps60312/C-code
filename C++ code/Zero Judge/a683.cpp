#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,K;
LL Solve1()
{
	LL ans=0LL;
	for(int i=1;i<=N;i++)ans+=K%i;//equals to K-K/i*i
	return ans;
}
LL Solve2()
{
	LL ans=(LL)K*N;
	for(int i=1;i<=N;i++)ans-=K/i*i;
	return ans;
}
LL Solve3()
{
	LL ans=(LL)K*N;
	for(int i=1;i<=N;i++)
	{
		if(K/i==0LL)break;
		const int j=min(N,K/(K/i));
		ans-=K/i*((LL)(i+j)*(j-i+1)/2LL);
		i=j;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		printf("%lld\n",Solve3());
	}
	return 0;
}
