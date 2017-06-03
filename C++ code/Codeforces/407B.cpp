#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int N,S[1001];
LL DP[1001],ANS[1002];
//DP[i]: from odd to even
//ANS[i]: get to cell i
LL GetANS(const int i);
LL GetDP(const int loc)
{
	LL &ans=DP[loc];
	if(ans!=-1LL)return ans;
	ans=0LL;
	for(int i=S[loc];i<loc;i++)(ans+=1LL+GetDP(i))%=MOD;
	(ans+=1)%=MOD;
	return ans;
}
LL GetANS(const int loc)
{
	LL &ans=ANS[loc];
	if(ans!=-1LL)return ans;
	ans=(GetANS(loc-1)+GetDP(loc-1)+1LL)%MOD;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=0;i<=N+1;i++)DP[i]=ANS[i]=-1LL;
		ANS[0]=DP[0]=0;
		printf("%lld\n",(GetANS(N+1)-1LL+MOD)%MOD);
	}
	return 0;
}
