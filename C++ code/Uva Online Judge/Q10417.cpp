#include<cstdio>
int T,N,S[5],VIS[12];
double F[12][5];
void dfssum(int i,int cnt,double p,int g,double &ans)
{
	p*=F[i][g],cnt--;
	if(cnt==0){ans+=p;return;}
	for(i=0;i<N;i++)
	{
		if(VIS[i])continue;
		VIS[i]=1;
		dfssum(i,cnt,p,g,ans);
		VIS[i]=0;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<5;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)
		{
			VIS[i]=0;
			for(int j=0;j<5;j++)
			{
				scanf("%lf",&F[i][j]);
			}
		}
		int af;
		double ap=0.0,sum,f,ta;
		for(int i=0;i<5;i++)
		{
			f=0.0;
			dfssum(0,S[i],1.0,i,f);
			sum=f;
			for(int j=1;j<N;j++)dfssum(j,S[i],1.0,i,sum);
			printf("sum=%.3lf,f=%.3lf\n",sum,f);
			ta=f/sum;
			if(ta>ap)ap=ta,af=i;
		}
		printf("%d %.3f\n",af,ap);
	}
	return 0;
}
