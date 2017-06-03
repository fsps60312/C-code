#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
bool getmax(LL &a,const LL b){if(b>a){a=b;return true;}return false;}
int N,K;
LL S[500000],SUM[500001],DP[500001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		SUM[N]=0LL;
		for(int i=N-1;i>=0;i--)SUM[i]=SUM[i+1]+S[i];
		//DP[i]=max(SUM[i]+DP[j]-(j-i)^2)
		DP[N]=0LL;
		for(int i=N-1;i>=0;i--)
		{
			DP[i]=-INF;
			int k=-1;
			for(int j=i+1;j<=i+K;j++)if(getmax(DP[i],SUM[i]+DP[j]-(LL)(j-i)*(j-i)))k=j;
//			printf("DP[%d]=%lld,k=%d\n",i,DP[i],k);
		}
		printf("%lld\n",DP[0]-SUM[0]);
	}
	return 0;
}
