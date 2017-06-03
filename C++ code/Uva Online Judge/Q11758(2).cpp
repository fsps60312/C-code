#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int T,N,K,D;
LL C[10001][101],ANS;
LL CNT[16];
void Dfs(const LL &now,const int dep)
{
	if(dep==16)
	{
		//N=4,K=2,now=1: 2
		//***___****____=C(9,2)
		LL ta=C[N-K-now+K/2LL][K/2LL];
		for(int i=0;i<16;i++)
		{
			(ta*=C[K/2LL][CNT[i]])%=MOD;
			if(i==15)assert(CNT[i]==0LL);
		}
		(((ANS-=ta)%=MOD)+=MOD)%=MOD;
		//printf("(ta=%2lld,now=%2lld):",ta);
		//for(int i=0;i<16;i++)printf(" %lld",CNT[i]);puts("");
		return;
	}
	for(LL &cnt=CNT[dep]=0LL;cnt<=K/2&&now+cnt*(1LL<<dep)<=N-K;cnt+=(D+1LL))
	{
		Dfs(now+cnt*(1LL<<dep),dep+1);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=1;i<=10000;i++)
	{
		C[i][0]=1LL;
		if(i<=100)C[i][i]=1LL;
		for(int j=1;j<=100&&j<i;j++)((C[i][j]=C[i-1][j-1])+=C[i-1][j])%=MOD;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&K,&D);
		ANS=C[N][K];
		printf("a:%lld\n",ANS);
//N-(sum+K/2)
		Dfs(0LL,0);
		printf("%lld\n",ANS);
	}
}
