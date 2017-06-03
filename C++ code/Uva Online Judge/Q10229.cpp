#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL MOD;
struct Matrix
{
	LL S[2][2];
};
Matrix operator*(const Matrix &a,const Matrix &b)
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
	{
		LL &v=ans.S[i][j]=0;
		for(int k=0;k<2;k++)(v+=a.S[i][k]*b.S[k][j])%=MOD;
	}
	return ans;
}
Matrix Pow(Matrix a,int p)
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)ans.S[i][j]=(i==j?1:0);
	for(;p;p>>=1)
	{
		if(p&1)ans=ans*a;
		a=a*a;
	}
	return ans;
}
LL Solve(const int n)
{
	if(n==0)return 0;
	Matrix m;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)m.S[i][j]=0;
	m.S[1][0]=1,m.S[1][1]=1,m.S[0][1]=1;
	m=Pow(m,n);
	return m.S[1][0];
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int m;scanf("%d%d",&N,&m)==2;)
	{
		MOD=1<<m;
		printf("%lld\n",Solve(N));
	}
	return 0;
}
