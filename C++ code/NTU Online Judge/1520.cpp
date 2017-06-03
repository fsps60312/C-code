#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL A,B,MOD,DP[10],ANS;
void Dfs(const int depth,const LL now)
{
	if(B<now)return;
	assert(depth<10);
	if(A<=now)
	{
		LL ta=0;
		for(int i=0;i<=depth;i++)(ta+=DP[depth])%=MOD;
		(ANS+=ta)%=MOD;
		(DP[depth]+=ta+1)%=MOD;
	}
	for(LL d=0;d<=9;d++)Dfs(depth+1,now*10+d);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&A,&B,&MOD)==3)
	{
		{
			LL v=1LL;
			while(A/v!=B/v)v*=10;
			A%=v,B%=v;
		}
		for(int i=0;i<10;i++)DP[i]=0;
		ANS=0;
		for(int i=1;i<=9;i++)Dfs(0,i);
		printf("%lld\n",ANS);
	}
	return 0;
}
