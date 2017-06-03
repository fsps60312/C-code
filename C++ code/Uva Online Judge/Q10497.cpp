#include<cstdio>
typedef long long LL;
LL N;
LL C[801][801],LEVEL[801];
int main()
{
	LEVEL[0]=1LL;
	for(int i=1;i<=800;i++)
	{
		LEVEL[i]=LEVEL[i-1]*i;
		C[i][0]=C[i][i]=1LL;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	while(scanf("%lld",&N)==1&&N!=-1LL)
	{
		LL ans=0LL;
		for(int i=0;i<=N;i++)
		{
			if(i%2==0)ans+=C[N][i]*LEVEL[N-i];
			else ans-=C[N][i]*LEVEL[N-i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
