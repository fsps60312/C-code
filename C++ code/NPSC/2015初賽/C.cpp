#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL N,M;
struct Matrix
{
	vector<vector<LL> >s;
	Matrix(const int n){s.resize(n);for(auto &v:s)v.resize(n);}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans=Matrix(M);
		for(int i=0;i<M;i++)for(int j=0;j<M;j++)
		{
			LL &v=ans.s[i][j]=0LL;
			for(int k=0;k<M;k++)(v+=s[i][k]*a.s[k][j])%=MOD;
		}
		return ans;
	}
};
Matrix Pow(Matrix a,LL p)
{
	Matrix ans=Matrix(M);
	for(int i=0;i<M;i++)for(int j=0;j<M;j++)ans.s[i][j]=(i==j?1LL:0LL);
	while(p)
	{
		if(p&1LL)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
LL DP[501];
#include<cstdlib>
int main()
{
//	N=1000000000000000000LL,M=500;
//	N=1000000000000000000LL,M=50;
	while(scanf("%lld%lld",&N,&M)==2)
	{
		DP[0]=1LL;
		for(int i=1;i<=M;i++)
		{
			DP[i]=0LL;
			for(int j=0;j<i;j++)(DP[i]+=DP[j])%=MOD;
		}
		if(N<=M)printf("%lld\n",DP[N]);
		else
		{
			Matrix a=Matrix(M);
			for(int i=0;i<M;i++)for(int j=0;j<M;j++)a.s[i][j]=0LL;
			for(int i=0;i<M;i++)a.s[0][i]=1LL;
			for(int i=1;i<M;i++)a.s[i][i-1]=1LL;
			a=Pow(a,N-M+1LL);
			LL ans=0LL;
			for(int i=0;i<M;i++)(ans+=a.s[0][i]*DP[M-1-i])%=MOD;
			printf("%lld\n",ans);
		}
	}
	system("pause");
	return 0;
}
