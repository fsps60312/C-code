#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,S,T[10001],C[10001],TSUM[10001],CSUM[10001],DP[10002];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%d",&S);
		for(int i=1;i<=N;i++)scanf("%d%d",&T[i],&C[i]),TSUM[i]=TSUM[i-1]+T[i],CSUM[i]=CSUM[i-1]+C[i];
		DP[N+1]=0;
		for(int i=N;i>=1;i--)
		{
			DP[i]=INF;
			for(int j=i;j<=N;j++)getmin(DP[i],(S+TSUM[j]-TSUM[i-1])*(CSUM[N]-CSUM[i-1])+DP[j+1]);
		}
		printf("%d\n",DP[1]);
	}
	return 0;
}
