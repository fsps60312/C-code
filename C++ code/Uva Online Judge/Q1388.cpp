#include<cstdio>
#include<cmath>
int N,M;
double mod(double a,double b)
{
	return a-b*(int)(a/b);
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		M+=N;
		double p;
		double d1=10000.0/N;
		double d2=10000.0/M;
		double ans=0.0;
		for(int i=0;i<N;i++)
		{
			p=mod(d1*i,d2);
			//printf("p=%.4f\n",p);
			ans+=p<=0.5*d2?p:d2-p;
		}
		printf("%.4f\n",ans);
	}
	return 0;
}
