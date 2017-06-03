#include<cstdio>
int T,A,B,N,M,MOD;
struct Matrix
{
	int v[2][2];
	Matrix operator*(Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				int &b=ans.v[i][j]=0;
				for(int k=0;k<2;k++)
				{
					b+=v[i][k]*a.v[k][j];
					b%=MOD;
				}
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix &a){return (*this)=(*this)*a;}
}MUL;
Matrix I()
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)ans.v[i][j]=i==j?1:0;
	return ans;
}
Matrix pow(Matrix a,int p)
{
	Matrix b=I();
	while(p)
	{
		if(p&1)b*=a;
		a*=a;
		p>>=1;
	}
	return b;
}
int solve()
{
	A%=MOD,B%=MOD;
	if(N<2)return N?B:A;
	MUL.v[0][0]=MUL.v[0][1]=MUL.v[1][0]=1;
	MUL.v[1][1]=0;
	MUL=pow(MUL,N-1);
	return (MUL.v[0][0]*B+MUL.v[0][1]*A)%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&A,&B,&N,&M);
		MOD=1;while(M--)MOD*=10;
		printf("%d\n",solve());
	}
	return 0;
}
