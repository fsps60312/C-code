#include<cstdio>
#include<cassert>
using namespace std;
struct Spe
{
	double r,s,p;
	Spe(){}
	Spe(const double _r,const double _s,const double _p):r(_r),s(_s),p(_p){}
};
Spe operator*(const Spe &a,const double b){return Spe(a.r*b,a.s*b,a.p*b);}
Spe operator+(const Spe &a,const Spe &b){return Spe(a.r+b.r,a.s+b.s,a.p+b.p);}
int R,S,P;
Spe DP[101][101][101];
Spe GetDP(const int r,const int s,const int p)
{
	Spe &dp=DP[r][s][p];
	if(dp.r!=-1.0)return dp;
	if(r&&!s&&!p)return dp=Spe(1.0,0.0,0.0);
	if(s&&!r&&!p)return dp=Spe(0.0,1.0,0.0);
	if(p&&!s&&!r)return dp=Spe(0.0,0.0,1.0);
	double sum=r*s+s*p+r*p;
	dp=Spe(0.0,0.0,0.0);
	if(r)dp=dp+GetDP(r-1,s,p)*(r*p/sum);
	if(s)dp=dp+GetDP(r,s-1,p)*(r*s/sum);
	if(p)dp=dp+GetDP(r,s,p-1)*(s*p/sum);
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)for(int k=0;k<=100;k++)DP[i][j][k].r=-1.0;
	while(scanf("%d%d%d",&R,&S,&P)==3)
	{
		const Spe &ans=GetDP(R,S,P);
		printf("%.10f %.10f %.10f\n",ans.r,ans.s,ans.p);
	}
	return 0;
}
