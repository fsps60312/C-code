#include<cstdio>
#include<cstdlib>
//#include<cmath>
int T,n,m,k;
double f[1000],p[1000];
double pow(double a,int b)
{
	double ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
		}
		b/=2;
		a*=a;
	}
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
		f[0]=p[0];
		for(int i=1;i<m;i++)
		{
			f[i]=p[0];
			for(int j=1;j<n;j++) f[i]+=p[j]*pow(f[i-1],j);
		}
		printf("Case #%d: %.7lf\n",kase,pow(f[m-1],k));
	}
	return 0;
}
