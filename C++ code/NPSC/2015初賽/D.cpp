#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL DP[100001];
int T,N,S[100001],PRE[100001];
map<int,int>IDX;
int main()
{
//	freopen("inn.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		IDX.clear();
		for(int i=1;i<=N;i++)
		{
			auto it=IDX.find(S[i]);
			if(it==IDX.end())PRE[i]=-1;
			else PRE[i]=it->second;
			IDX[S[i]]=i;
		}
		DP[0]=1LL;
		for(int i=1;i<=N;i++)
		{
			if(PRE[i]==-1)(DP[i]=DP[i-1]*2LL)%=MOD;
			else (((DP[i]=DP[i-1]*2LL-DP[PRE[i]-1])%=MOD)+=MOD)%=MOD;
		}
		printf("%lld\n",(DP[N]+MOD-1LL)%MOD);
	}
	return 0;
}
