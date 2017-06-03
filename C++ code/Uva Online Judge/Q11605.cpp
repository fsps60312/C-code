#include<cstdio>
#include<cstdlib>
int T,n,m,p,K;
struct Matrix
{
	double s[2][2];
	Matrix operator*(Matrix a)
	{
		Matrix ans;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				ans.s[i][j]=0;
				for(int k=0;k<2;k++)
				{
					ans.s[i][j]+=s[i][k]*a.s[k][j];
				}
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix a)
	{
		return *this=*this*a;
	}
};
Matrix pow(Matrix a,int b)
{
	Matrix ans;
	ans.s[0][0]=ans.s[1][1]=1;
	ans.s[1][0]=ans.s[0][1]=0;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
		}
		b>>=1;
		a*=a;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d%d",&n,&m,&p,&K);
		double odd=0,sum=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				for(int l=1;l<=p;l++)
				{
					int o=(n-i+1)*(m-j+1)*(p-l+1);
					sum+=o;
					odd+=o*i*j*l;
				}
			}
		}
		odd/=sum;
		Matrix A;
		A.s[0][0]=A.s[1][1]=1-odd;
		A.s[1][0]=A.s[0][1]=odd;
		A=pow(A,K);
		//A.s[1][0]
		printf("Case %d: %.10lf\n",kase,A.s[1][0]*n*m*p);
	}
	return 0;
}
