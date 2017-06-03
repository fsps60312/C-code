#include<cstdio>
#include<cstdlib>
#include<cmath>
const double logt=log10(2);
int T,n;
double S,llog[50000],plog[50000];
double f(int a,int b)//C(a,b)/2^a
{
	double ans=1;
	if(b<=a/2) b=a-b;
	int c=a;
	for(int i=b+1;i<=a;i++)
	{
		ans*=i;
		ans/=i-b;
		while(c&&ans>1)
		{
			ans/=2;
			c--;
		}
	}
	while(c)
	{
		ans/=2;
		c--;
	}
	return ans;
}
int main()
{
	//printf("%lf\n",logt);
	llog[0]=plog[0]=0;
	for(int i=1;i<50000;i++)
	{
		plog[i]=plog[i-1]+logt;
		llog[i]=llog[i-1]+log10(i);
	}
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		n--;
		double ans=0;
		for(int i=0;i<=n;i++)
		{
			scanf("%lf",&S);
			//ans+=S*C(n,i)/pow(n);
			if(llog[n]-llog[i]-llog[n-i]-plog[n]>-8)
			{
				ans+=S*f(n,i);
			}
		}
		printf("Case #%d: %.3lf\n",kase,ans);
	}
	return 0;
}
