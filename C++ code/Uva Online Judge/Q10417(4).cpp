#include<cstdio>
int T,N,S[5],VIS[12];
double F[12][5];
double ANS[5];
void dfs(double p,int dep,int idx)
{
	if(p==0.0)return;
	if(dep==N)
	{
		ANS[idx]+=p;
		return;
	}
	for(int i=0;i<5;i++)
	{
		if(!S[i])continue;
		S[i]--;
		dfs(p*F[dep][i],dep+1,idx);
		S[i]++;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<5;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)for(int j=0;j<5;j++)scanf("%lf",&F[i][j]);
		for(int i=0;i<5;i++)
		{
			ANS[i]=0.0;
			if(!S[i])continue;
			S[i]--;
			dfs(F[0][i],1,i);
			S[i]++;
//			printf("ANS[%d]=%.3lf\n",i,ANS[i]);
		}
		int af;
		double ap=-1.0,sum=0.0;
		for(int i=0;i<5;i++)
		{
			double &ta=ANS[i];
			sum+=ta;
			ta/=S[i];
			if(ta>ap)ap=ta,af=i;
		}
//		printf("%.3lf\n",1.0/sum);
		printf("%d %.3f\n",af+1,ap/sum);
	}
	return 0;
}
