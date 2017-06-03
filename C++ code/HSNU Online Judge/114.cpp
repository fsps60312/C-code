#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int T,N;
char S[500001];
LL DP[2][500000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		N=-1;while(S[++N])DP[0][N]=DP[1][N]=INF;
		int mx=1;
		DP[0][0]=0LL;
		int d=0;
		for(int i=0;i<N;i++,d^=1)
		{
			LL cost[2];
			if(S[i]=='?')scanf("%lld%lld",&cost[0],&cost[1]);
			else cost[0]=cost[1]=0LL;
//			printf("(%lld,%lld)\n",cost[0],cost[1]);
			for(int j=0;j<mx;j++)
			{
				if(DP[d][j]==INF)continue;
				if( S[i]=='('||S[i]=='?'      )getmin(DP[d^1][j+1],DP[d][j]+cost[0]);
				if((S[i]==')'||S[i]=='?')&&j>0)getmin(DP[d^1][j-1],DP[d][j]+cost[1]);
				DP[d][j]=INF;
			}
			if(S[i]=='('||S[i]=='?')mx++;
			mx=min(mx,N-i);
		}
		if(DP[d][0]==INF)puts("IMBA");
		else printf("%lld\n",DP[d][0]);
	}
	return 0;
}
