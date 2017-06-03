#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF=2147483647;
LL N,L;
LL W[100001],H[100001],SUM[100001];
LL DP[100001];
int main()
{
	scanf("%lld%lld",&N,&L);
	SUM[0]=DP[0]=0;
	for(LL i=1;i<=N;i++)
	{
		scanf("%lld%lld",&H[i],&W[i]);
		SUM[i]=SUM[i-1]+W[i];
		DP[i]=INF;
	}
	for(LL i=1;i<=N;i++)
	{
		for(LL j=i,mx=H[i];j>0&&SUM[i]-SUM[j-1]<=L;j--,mx=max(mx,H[j]))DP[i]=min(DP[i],DP[j-1]+mx);
	}
//	for(LL i=1;i<=N;i++)printf(" %lld",DP[i]);puts("");
	printf("%lld\n",DP[N]);
	return 0;
}
