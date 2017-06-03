#include<cstdio>
#include<cstdlib>
//#include<cmath>
int T,n;
double S,pow[50000],level[50000];
double C(int a,int b)
{
	return level[a]/level[b]/level[a-b];
}
int main()
{
	pow[0]=1;
	level[0]=1;
	for(int i=1;i<50000;i++)
	{
		pow[i]=pow[i-1]*2;
		level[i]=level[i-1]*i;
	}
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	double ans;
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		n--;
		ans=0;
		for(int i=0;i<=n;i++)
		{
			scanf("%lf",&S);
			//printf(" %lf %lf\n",S,C(n,i));
			ans+=S*C(n,i);
		}
		//ans/=pow(2,n);//2^n
		printf("Case #%d: %.3lf\n",kase,ans/pow[n]);
	}
	return 0;
}
