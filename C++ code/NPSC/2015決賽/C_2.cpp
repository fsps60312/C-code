#include<cstdio>
#include<algorithm>
using namespace std;
double N;
double A,B,C;
double DP[10001][3][3];
void getmax(double &a,const double b){if(b>a)a=b;}
double GetDP(const int n,const int a,const int b)
{
	if(a+b>=3)
	{
		if(b>0)return GetDP(n,a,b-1)+60.0;
		else return GetDP(n,a-1,b)+40.0;
	}
	double &dp=DP[n][a][b];
	if(dp!=-1.0)return dp;
	if(n==0)return a*40.0+b*60.0;
	dp=0.0;
	
	double ans1,ans2;//replace, not replace
	ans1=GetDP(n-1,a,b);
	double ta=a,tb=b;
	if(ta>0)ta--;
	else if(tb>0)tb--;
	else
	{
		ans2=ans1;
		goto skip;
	}
	ans2=C*(100.0+GetDP(n-1,ta,tb))+B*GetDP(n-1,ta,tb+1)+A*GetDP(n-1,ta+1,tb);
	skip:;
	dp+=C*(100.0+max(ans1,ans2));
	
	ans1=GetDP(n-1,a,b+1);
	ta=a,tb=b+1;
	if(ta>0)ta--;
	else tb--;
	ans2=C*(100.0+GetDP(n-1,ta,tb))+B*GetDP(n-1,ta,tb+1)+A*GetDP(n-1,ta+1,tb);
	dp+=B*max(ans1,ans2);
	
	ans1=GetDP(n-1,a+1,b);
	ta=a+1,tb=b;
	ta--;
	ans2=C*(100.0+GetDP(n-1,ta,tb))+B*GetDP(n-1,ta,tb+1)+A*GetDP(n-1,ta+1,tb);
	dp+=A*max(ans1,ans2);
	return dp;
}
int main()
{
//	freopen("C.txt","r",stdin);
	while(scanf("%lf",&N)==1)
	{
		scanf("%lf%lf%lf",&A,&B,&C);
		A/=100.0,B/=100.0,C/=100.0;
		for(int i=0;i<=N;i++)for(int j=0;j<9;j++)DP[i][j/3][j%3]=-1.0;
		printf("%.10f\n",GetDP(N,0,0));
	}
	return 0;
}
