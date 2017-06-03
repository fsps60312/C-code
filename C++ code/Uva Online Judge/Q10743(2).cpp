#include<cstdio>
const int MOD=10000;
struct Matrix
{
	int s[3][3];
	Matrix(){}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				ans.s[i][j]=0;
				for(int k=0;k<3;k++)(ans.s[i][j]+=s[i][k]*a.s[k][j])%=MOD;
			}
		}
		return ans;
	}
};
Matrix Pow(Matrix a,int b)
{
	Matrix ans;
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans.s[i][j]=(i==j?1:0);
	while(b)
	{
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int T,N;
int Solve()
{
	if(N==4)return 19;
	if(N==3)return 6;
	if(N==2)return 2;
	if(N==1)return 1;
	int tmp[][3]={{5,-7,4},{1,0,0},{0,1,0}};
	N-=4;
	Matrix a;
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)a.s[i][j]=tmp[i][j];
	a=Pow(a,N);
	return ((19*a.s[0][0]+6*a.s[0][1]+2*a.s[0][2])%MOD+MOD)%MOD;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		static int kase=1;
		printf("Case %d: ",kase++);
		if(N<10)printf("%d\n",Solve());
		else printf("%04d\n",Solve());
	}
	return 0;
}
