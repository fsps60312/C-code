#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
struct Matrix
{
	double S[2][2];
};
Matrix operator*(const Matrix &a,const Matrix &b)
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
	{
		double &v=ans.S[i][j]=0.0;
		for(int k=0;k<2;k++)v+=a.S[i][k]*b.S[k][j];
	}
	return ans;
}
Matrix Pow(Matrix a,LL p)
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)ans.S[i][j]=(i==j?1.0:0.0);
	for(;p;p>>=1)
	{
		if(p&1LL)ans=ans*a;
		a=a*a;
	}
	return ans;
}
LL F0,F1,N;
double A,B;
double Solve()
{
	if(N==1)return F0;
	else if(N==2)return F1;
	Matrix m;
	m.S[0][0]=A;
	m.S[0][1]=1.0;
	m.S[1][0]=B;
	m.S[1][1]=0.0;
	m=Pow(m,N-1LL);
	return F1*m.S[0][0]+F0*m.S[1][0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld%lf%lf%lld",&F0,&F1,&A,&B,&N);
		printf("%.0f\n",Solve());
	}
	return 0;
}
