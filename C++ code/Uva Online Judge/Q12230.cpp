#include<cstdio>
int N,D;
int main()
{
	int kase=1;
	while(scanf("%d%d",&N,&D)==2&&(N||D))
	{
		double ans=D;
		double p,l,v;
		for(int i=0;i<N;i++)
		{
			scanf("%lf%lf%lf",&p,&l,&v);
			ans+=2.0*l/v;
			ans-=l;
		}
		printf("Case %d: %.3lf\n\n",kase++,ans);
	}
	return 0;
}
