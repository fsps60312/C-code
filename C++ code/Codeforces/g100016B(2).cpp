#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double INF=1e100,EPS=1e-7,PI=acos(-1.0);
void getmax(double &a,const double &b){if(b>a)a=b;}
bool getmax(double &a,const double &b1,const double &b2)
{
	if(b1==-INF||b2==-INF)return false;
	if(b1+b2>a){a=b1+b2;return true;}
	return false;
}
int N,K;
struct Matrix
{
	double S[2000][2000];
//	void Mul(const Matrix &a,const Matrix &b)
//	{
//		static Matrix ans;
//		for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)
//		{
//			double &v=ans.S[i][j]=-INF;
//			for(int k=0;k<N*2;k++)if(a.S[i][k]!=-INF&&b.S[k][j]!=-INF)getmax(v,a.S[i][k]+b.S[k][j]);
//		}
//		for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)S[i][j]=ans.S[i][j];
//	}
	void Solve(const int from,const int l,const int r,const int bl,const int br,Matrix &ans,const Matrix &a,const Matrix &b)const
	{
		if(l>r)return;
		const int mid=(l+r)/2;
		int bm=bl;
		double &v=ans.S[from][mid]=-INF;
//		for(int i=from;i<=mid;i++)
		for(int i=bl;i<=br&&i<=mid;i++)
		{
			if(getmax(v,a.S[from][i],b.S[i][mid]))bm=i;
		}
		Solve(from,l,mid-1,bl,bm,ans,a,b),Solve(from,mid+1,r,bm,br,ans,a,b);
	}
	void Mul(const Matrix &a,const Matrix &b)
	{
		static Matrix ans;
		for(int i=0;i<N*2;i++)
		{
			for(int j=0;j<i;j++)ans.S[i][j]=-INF;
			Solve(i,i,N*2-1,i,N*2-1,ans,a,b);
		}
		for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)S[i][j]=ans.S[i][j];
	}
//	void Print()
//	{
//		for(int i=0;i<N*2;i++)
//		{
//			for(int j=0;j<N*2;j++)
//			{
//				double &v=S[i][j];
//				if(v==-INF)printf("-.--- ");
//				else printf("%.3f ",v==-INF?0.0:v);
//			}
//			puts("");
//		}
//		puts("");
//	}
};
struct Opl
{
	double angle;
	int id;
	bool operator<(const Opl &o)const{return angle<o.angle;}
};
Opl OPL[2000];
double DP[2000][2000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lf",&OPL[i].angle),OPL[i].id=i+1;
		sort(OPL,OPL+N);
		for(int i=0;i<N;i++)OPL[N+i].id=OPL[i].id,OPL[N+i].angle=OPL[i].angle+2.0*PI;
		static Matrix m[12];
		for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)
		{
			double &v=m[0].S[i][j]=-INF;
			if(i<j&&OPL[j].angle-OPL[i].angle-EPS<=PI)v=0.5*sin(OPL[j].angle-OPL[i].angle);
		}
		int bound=0;
		for(int i=1;(1<<i)<=K;i++)m[i].Mul(m[i-1],m[i-1]),bound=i;
		static Matrix mans;
		for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)mans.S[i][j]=(i==j?0.0:-INF);
		for(int i=bound;i>=0;i--)if(K&(1<<i))mans.Mul(mans,m[i]);
		double ans=0.0;
		for(int i=0;i<N;i++)getmax(ans,mans.S[i][i+N]);
		printf("%.3lf\n",ans);
	}
	return 0;
}
