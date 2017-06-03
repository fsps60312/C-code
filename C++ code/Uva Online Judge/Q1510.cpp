#include<cstdio>
int T,N,NEON[1000][1000],C[1000][2];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)C[i][0]=C[i][1]=0;
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<N;j++)
			{
				int &n=NEON[i][j];
				scanf("%d",&n);
				NEON[j][i]=n;
				C[i][n]++,C[j][n]++;
			}
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(j==i)continue;
				ans+=C[j][NEON[i][j]^1];
			}
		}
		if(ans&3)printf("error\n");
		ans>>=2;
		printf("%d\n",N*(N-1)*(N-2)/6-ans);
	}
	return 0;
}
