#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Factory
{
	LL X,P,C;
}F[1000000];
int N;
LL DP[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lld%lld%lld",&F[i].X,&F[i].P,&F[i].C);
	DP[N-1]=F[N-1].C;
	for(int i=N-2;i>=0;i--)
	{
		DP[i]=INF;
		for(int j=i+1;j<N;j++)getmin(DP[i],DP[j]);
		DP[i]+=F[i].C;
		for(int j=i+1;j<N;j++)DP[j]+=F[i].P*(F[j].X-F[i].X);
	}
	LL ans=INF;
	for(int i=0;i<N;i++)getmin(ans,DP[i]);
	printf("%lld\n",ans);
	return 0;
}
