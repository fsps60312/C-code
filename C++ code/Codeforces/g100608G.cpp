#include<cstdio>
#include<cassert>
using namespace std;
int D,B;
int DP1[3000][3000],DP2[3000][3000];
double Pow(double a,int b)
{
	double ans=1;
	for(int i=0;i<b;i++)ans*=a;
	return ans;
}
double Lev(int a)
{
	double ans=1;
	for(int i=2;i<a;i++)ans*=i;
	return ans;
}
double C(int a,int b){return Lev(a)/Lev(b)/Lev(a-b);}
int main()
{
	for(int d=1;d<=10;d++)for(int b=1;b<=10;b++)if(Pow(b+1,d)<3000.1)
	{
		double ans=0;
		for(int i=0;i<=d;i++)ans+=Pow(C(d,i),2);
		printf("%.0f\n",ans);
	}
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&D,&B)==2)
	{
		if(D==0&&B==0)break;
		
	}
	return 0;
}
