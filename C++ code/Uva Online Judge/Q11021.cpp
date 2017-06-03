#include<cstdio>
#include<cstdlib>
#include<cmath>
int T,n,k,m;
double f[1000],p[1000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++)
		{
			scanf("%lf",&p[i]);
		}
		double e=0;
		for(int i=1;i<n;i++)
		{
			e+=p[i]*i;
		//printf("e:%lf\n",e);
		}
		e/=(1-p[0]);
		f[0]=pow(p[0],k);//died out after 1 day
		double now=e;
		for(int i=1;i<m;i++)
		{
			f[i]=f[i-1]+(1-f[i-1]/*living*/)*pow(p[0],now);
			now*=e;
		}
		printf("Case #%d: %.7lf\n",kase,f[m-1]);
	}
	return 0;
}
