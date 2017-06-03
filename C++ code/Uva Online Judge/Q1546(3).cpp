#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
int T,L,R;
double S[100];
bool AllSame()
{
	for(int i=1;i<L;i++)if(S[i]!=S[0])return false;
	return true;
}
bool Zero(const double &a){return fabs(a)<EPS;}
struct Matrix
{
	vector<vector<double> >s;
	int n;
	Matrix(const int _n):n(_n){s.resize(n);for(auto &v:s)v.resize(n+1);}
	void Swap(const int r1,const int r2){for(int i=0;i<=n;i++)swap(s[r1][i],s[r2][i]);}
	void Mul(const int r,const double &v){for(int i=0;i<=n;i++)s[r][i]*=v;}
	void Sub(const int r1,const int r2,const double &v){for(int i=0;i<=n;i++)s[r2][i]-=s[r1][i]*v;}
	void Eliminate(const int r1,const int r2,const int c)
	{
		if(Zero(s[r2][c]))return;
		Sub(r1,r2,s[r2][c]/s[r1][c]);
	}
};
double GetValue(const vector<double>&equ,const double &v)
{
	double ans=0.0,tmp=1.0;
	for(int i=0;i<equ.size();i++)ans+=tmp*equ[i],tmp*=v;
	return ans;
}
bool Solve(const int n,vector<double>&ans)
{
	Matrix board=Matrix(n);
	vector<vector<double> >&s=board.s;
	for(int i=0;i<n;i++)
	{
		s[i][n]=S[i];
		double tmp=1.0;
		for(int j=0;j<n;j++,tmp*=(double)i)s[i][j]=tmp;
	}
	for(int i=0;i<n;i++)
	{
		if(Zero(s[i][i]))
		{
			bool found=false;
			for(int j=i+1;j<n;j++)if(!Zero(s[j][i])){board.Swap(i,j);found=true;break;}
			assert(found);
		}
		for(int j=i+1;j<n;j++)board.Eliminate(i,j,i),assert(Zero(s[j][i]));
	}
	for(int i=n-1;i>=0;i--)for(int j=i-1;j>=0;j--)board.Eliminate(i,j,i),assert(Zero(s[j][i]));
	ans.clear();
	for(int i=0;i<n;i++)ans.push_back(s[i][n]/s[i][i]);
	return true;
}
void Solve()
{
	vector<double>ans;
	assert(Solve(L,ans));
	for(int i=L;i<R;i++)S[i]=GetValue(ans,i);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&L,&R);
		R+=L;
		for(int i=0;i<L;i++)scanf("%lf",&S[i]);
		if(AllSame())for(int i=L;i<R;i++)S[i]=S[0];
		else Solve();
		for(int i=L;i<R;i++)
		{
			if(i>L)putchar(' ');
			printf("%.0f",S[i]);
		}
		puts("");
	}
	return 0;
}
