#include<cstdio>
#include<cassert>
using namespace std;
const double EPS=1e-15;
struct Matrix
{
	double S[52][52];
};
Matrix operator*(const Matrix &a,const Matrix &b)
{
	Matrix ans;
	for(int i=1;i<=51;i++)for(int j=1;j<=51;j++)
	{
		double &v=ans.S[i][j]=0.0;
		for(int k=1;k<=51;k++)v+=a.S[i][k]*b.S[k][j];
	}
	return ans;
}
Matrix Pow(Matrix a,int p)
{
	Matrix ans;
	for(int i=1;i<=51;i++)for(int j=1;j<=51;j++)ans.S[i][j]=(i==j?1.0:0.0);
	for(;p;p>>=1,a=a*a)if(p&1)ans=ans*a;
	return ans;
}
int N;
double P,Q;
double Solve()
{
	static double a[52][51],b[52][51];//spaces, value: possibility
	for(int i=0;i<=51;i++)for(int j=0;j<=50;j++)a[i][j]=b[i][j]=0.0;
	for(int i=1;i<=51;i++)
	{
		for(int v=1;v<=50;v++)
		{
			if(v==1)a[i][v]+=P;
			if(v==2)a[i][v]+=Q,b[i][v]+=Q;
			a[i][v]+=a[i][v-1]*a[i-1][v-1];
			b[i][v]+=b[i][v-1]*a[i-1][v-1];
		}
	}
//	for(int i=1;i<=50;i++)printf("a[3][%d]=%.10f\n",i,a[3][i]);
	for(int space=51;space>=1;space--)
	{
		for(int v=1;v<=50;v++)
		{
			a[space][v]*=1.0-a[space-1][v];
			b[space][v]*=1.0-a[space-1][v];
		}
	}
	static double dp[52][52],sum[51][51];//slime count, value: excepted sum
	for(int v=1;v<=50;v++)dp[1][v]=v;
	for(int slime=2;slime<=50;slime++)
	{
		for(int v=1;v<=50;v++)
		{
			double &d=dp[slime][v]=0.0,&s=sum[slime][v]=0.0;
			for(int nxt=1;nxt<=50;nxt++)if(nxt!=v)
			{
				if(v==1)
				{
					d+=dp[slime-1][nxt]*b[slime-1][nxt];
					s+=b[slime-1][nxt];
				}
				else if(v>nxt)
				{
					d+=dp[slime-1][nxt]*a[slime-1][nxt];
					s+=a[slime-1][nxt];
				}
			}
//			assert(s!=0.0);
//			printf("sum=%.10f\n",s);
			d=v+d/s;
		}
	}
	if(N>50)
	{
		Matrix m;
		for(int i=1;i<=51;i++)for(int j=1;j<=51;j++)m.S[i][j]=0.0;
		m.S[51][51]=1.0;
		for(int v=1;v<=50;v++)
		{
			for(int nxt=1;nxt<=50;nxt++)if(v!=nxt)
			{
				if(v==1)m.S[nxt][v]+=b[51][nxt]/sum[50][v];
				else if(v>nxt)m.S[nxt][v]+=a[51][nxt]/sum[50][v];
			}
			m.S[51][v]=v;
		}
		m=Pow(m,N-50);
//		printf("m.S[51][51]=%.10f\n",m.S[51][51]);
//		for(int i=1;i<=50;i++)printf("m.S[51][%i]=%.10f\n",i,m.S[51][i]);
		dp[50][51]=1.0;
		for(int v=1;v<=50;v++)
		{
			double &d=dp[51][v]=0.0;
			for(int nxt=1;nxt<=51;nxt++)
			{
				d+=dp[50][nxt]*m.S[nxt][v];
			}
		}
		N=51;
	}
	double ans=0.0;
	for(int i=1;i<=50;i++)if(a[N][i]!=0.0)ans+=dp[N][i]*a[N][i];
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&P)==2)
	{
		P/=1e9,Q=1.0-P;
		printf("%.10f\n",Solve());
	}
	return 0;
}
