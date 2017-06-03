#include<cstdio>
const int MOD=1000000007;
int T,N,K;
int DP[1000][1001][4],SUM[1000][1001][4];
int min(int a,int b){return a<b?a:b;}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)for(int j=0;j<=N;j++)for(int k=0;k<4;k++)DP[i][j][k]=SUM[i][j][k]=0;
		//10
		//01
		//11
		DP[0][1][1]=SUM[0][1][1]=SUM[1][1][1]=1;
		DP[1][1][2]=SUM[1][1][2]=1;
		DP[1][2][3]=SUM[1][2][3]=1;
		for(int i=2;i<N;i++)DP[i][1][0]=SUM[i][1][0]=1;
		for(int i=2;i<N;i++)
		{
			for(int k=0;k<4;k++)SUM[i][1][k]=SUM[i-1][1][k]+DP[i][1][k];
			for(int j=2;j<=K;j++)
			{
				for(int k=0;k<3;k++)
				{
					int &dp=DP[i][j][k]=0;
					SUM[i][j][k]=SUM[i-1][j][k];
					if(i==2&&(k&1))continue;
					if(i==3&&(k&2))continue;
					dp+=DP[i-1][j-1][k],dp%=MOD;
					if(i>=3)dp+=SUM[i-3][j-1][k],dp%=MOD;
					SUM[i][j][k]+=dp,SUM[i][j][k]%=MOD;
				}
			}
		}
		for(int i=0;i<N;i++)for(int j=1;j<=K;j++)for(int k=0;k<4;k++)printf("(%d,%d,%d):%d,%d\n",i,j,k,DP[i][j][k],SUM[i][j][k]);
		int ans=0;
		for(int j=0;j<4;j++)ans+=SUM[N-1][K][j],ans%=MOD;
		ans-=DP[N-1][K][2],ans=(ans+MOD)%MOD;
		ans-=DP[N-1][K][3],ans=(ans+MOD)%MOD;
		if(N>=2)ans-=DP[N-2][K][1],ans=(ans+MOD)%MOD;
		if(N>=2)ans-=DP[N-2][K][3],ans=(ans+MOD)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
