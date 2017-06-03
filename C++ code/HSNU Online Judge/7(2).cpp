#include<cstdio>
int N;
struct Mat
{
	int v[2][2];
	Mat operator*(const Mat &a)
	{
		Mat ans;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				int &b=ans.v[i][j]=0;
				for(int k=0;k<2;k++)
				{
					b+=v[i][k]*a.v[k][j];
				}
				b%=10;
			}
		}
		return ans;
	}
}I,A;
Mat Pow(Mat a,int p)
{
	Mat ans=I;
	while(p)
	{
		if(p&1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
int Solve()
{
	Mat a=A;
	a=Pow(a,N-1);
	return (a.v[0][0]+a.v[1][0])%10;
}
int main()
{
	I.v[0][0]=I.v[1][1]=1;
	I.v[0][1]=I.v[1][0]=0;
	A.v[0][0]=A.v[1][0]=A.v[0][1]=1;
	A.v[1][1]=0;
//	DP[1][0]=1,DP[1][1]=0;
//	for(int i=2;i<=10000000;i++)
//	{
//		DP[i][0]=DP[i-1][0]+DP[i-1][1]%10;
//		DP[i][1]=DP[i-1][0]%10;
//	}
//	{1,1}{DP[i-1][0]}
//	{1,0}{DP[i-1][1]}
	while(scanf("%d",&N)==1)
	{
		printf("%d\n",Solve());
	}
	return 0;
}
