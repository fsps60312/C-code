#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int T,n;
double S,pow[50000];
vector<double> c[1000];
double C(int a,int b)
{
	if(a<1000) return c[a][b];
	if(b<=a/2) b=a-b;
	double ans=1;
	for(int i=b+1;i<=a;i++)
	{
		ans*=i;
		ans/=i-b;
	}
	return ans;
}
int main()
{
	pow[0]=1;
	c[0].push_back(1);
	for(int i=1;i<1000;i++)
	{
		pow[i]=pow[i-1]*2;
		c[i].push_back(1);
		for(int j=1;j<i;j++)
		{
			c[i].push_back(c[i-1][j-1]+c[i-1][j]);
		}
		c[i].push_back(1);
	}
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
