#include<cstdio>
int T,N,S[5],VIS[12];
double F[12][5];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<5;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)for(int j=0;j<5;j++)scanf("%lf",&F[i][j]);
		int af;
		double ap=-1.0,sum,f,ta;
		for(int i=0;i<5;i++)
		{
			sum=f=F[0][i];
			for(int j=1;j<N;j++)sum+=F[j][i];
			printf("sum=%.3lf,f=%.3lf\n",sum,f);
			if(sum==0.0)continue;
			ta=f/sum/S[i];
			if(ta>ap)ap=ta,af=i;
		}
		printf("%d %.3f\n",af+1,ap);
	}
	return 0;
}
