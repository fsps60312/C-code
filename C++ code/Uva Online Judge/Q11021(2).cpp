#include<cstdio>
#include<cstdlib>
#include<cmath>
int T,n,k,m;
double p[1000];
double f(int a)
{
	if(a==0) return p[0];
	double ans=p[0];
	for(int i=1;i<n;i++) ans+=p[i]*pow(f(a-1),i);
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++) scanf("%lf",&p[i]);
		printf("Case #%d: %.7lf\n",kase,pow(f(m-1),k));
	}
	return 0;
}
