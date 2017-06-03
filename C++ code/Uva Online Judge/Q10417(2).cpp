#include<cstdio>
int T,N,S[5],VIS[12];
double F[12][5];
void dfssum(int i,int cnt,double p,int g,double &ans)
{
	p*=F[i][g],cnt--;
	if(cnt==0){ans+=p;return;}
	for(i++;i<N;i++)dfssum(i,cnt,p,g,ans);
}
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
			f=0.0;
			dfssum(0,S[i],1.0,i,f);
			sum=f;
			for(int j=1;j<N;j++)dfssum(j,S[i],1.0,i,sum);
			printf("sum=%.3lf,f=%.3lf\n",sum,f);
			if(sum==0.0)continue;
			ta=f/sum/S[i];
			if(ta>ap)ap=ta,af=i;
		}
		printf("%d %.3f\n",af+1,ap);
	}
	return 0;
}
