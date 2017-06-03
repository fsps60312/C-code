#include<cstdio>
int K,N;
double CNT[100][10];
int main()
{
	while(scanf("%d%d",&K,&N)==2)
	{
		for(int i=0;i<=K;i++)CNT[0][i]=1.0;
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<=K;j++)
			{
				CNT[i][j]=CNT[i-1][j];
				if(j-1>=0)CNT[i][j]+=CNT[i-1][j-1];
				if(j+1<=K)CNT[i][j]+=CNT[i-1][j+1]; 
			}
		}
		double ans=0.0;
		for(int i=0;i<=K;i++)ans+=CNT[N-1][i];
		ans*=100.0;
		for(int i=0;i<N;i++)ans/=(K+1.0);
		printf("%.5f\n",ans);
	}
	return 0;
}
