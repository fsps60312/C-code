#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int N;
struct Matrix
{
	vector<vector<int> >s;
	Matrix(const int n){s.resize(n);for(auto &v:s)v.resize(n);}
	void SetFrom(const Matrix &m,const int r,const int c)
	{
		assert(m.s.size()==s.size()+1);
		for(int i=0,a=0;i<m.s.size();i++)if(i!=r)
		{
			for(int j=0,b=0;j<m.s.size();j++)if(j!=c)s[a][b]=m.s[i][j],b++;
			a++;
		}
	}
	void Sub(const int c1,const int c2,const int v){assert(v);for(int i=0;i<s.size();i++)s[i][c1]-=s[i][c2]*v;}
};
int GetDeterminant(Matrix &m,const int n)
{
	if(n==1)return m.s[0][0];
	for(;;)
	{
		int i1=-1,v1=0,i2=-1,v2=0;
		for(int i=0;i<n;i++)
		{
			const int v=abs(m.s[0][i]);
			if(v>=v1)i2=i1,v2=v1,i1=i,v1=v;
			else if(v>=v2)i2=i,v2=v;
		}
		if(v2==0)
		{
			if(v1==0)return 0;
			Matrix nxtm=Matrix(n-1);
			nxtm.SetFrom(m,0,i1);
			return (i1&1?-1:1)*m.s[0][i1]*GetDeterminant(nxtm,n-1);
		}
		m.Sub(i1,i2,m.s[0][i1]/m.s[0][i2]);
//		for(int i=0;i<n;i++)
//		{
//			for(int j=0;j<n;j++)printf(" %d",m.s[i][j]);puts("");
//		}
//		puts("");
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		Matrix m=Matrix(N);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&m.s[i][j]);
		printf("%d\n",GetDeterminant(m,N));
	}
	puts("*");
	return 0;
}
