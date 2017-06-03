#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Factory
{
	LL X,P,C;
}F[1000001];
int N;
LL DP[1000001],PROD[1000001],COST[1000001];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%lld%lld%lld",&F[i].X,&F[i].P,&F[i].C);
	PROD[0]=COST[0]=0LL;
	for(int i=1;i<=N;i++)
	{
		PROD[i]=PROD[i-1]+F[i].P;
		COST[i]=COST[i-1]+F[i].P*(F[N].X-F[i].X);
	}
//	for(int l=1,r=N;l<r;l++,r--)swap(F[l],F[r]);
	DP[0]=0LL;
	for(int i=1;i<=N;i++)
	{
		DP[i]=INF;
		for(int j=0;j<i;j++)
		{
			getmin(DP[i],DP[j]+(COST[i]-COST[j])-(PROD[i]-PROD[j])*(F[N].X-F[i].X));
		}
		DP[i]+=F[i].C;
//		printf("DP[%d]=%lld\n",i,DP[i]);
	}
	printf("%lld\n",DP[N]);
	return 0;
}
