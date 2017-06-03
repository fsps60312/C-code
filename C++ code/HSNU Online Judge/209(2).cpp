#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int N,M;
struct Matrix
{
	LL s[10][10];
	Matrix(){}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			LL &v=ans.s[i][j]=0LL;
			for(int k=0;k<N;k++)(v+=(LL)s[i][k]*a.s[k][j])%=MOD;
		}
		return ans;
	}
};
char BOTTLE[11][3][4];
bool SpotInside(const int idx)
{
	for(int i=0;i<2;i++)for(int j=0;j<3;j++)if(BOTTLE[idx][i][j]=='1'&&BOTTLE[idx][i+1][j]=='1')return true;
	for(int i=0;i<3;i++)for(int j=0;j<2;j++)if(BOTTLE[idx][i][j]=='1'&&BOTTLE[idx][i][j+1]=='1')return true;
	return false;
}
Matrix Pow(Matrix a,int p)
{
	Matrix ans;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.s[i][j]=(i==j?(SpotInside(i)?0LL:1LL):0LL);
	while(p)
	{
		if(p&1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<3;j++)scanf("%s",BOTTLE[i][j]);
		Matrix m;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(SpotInside(i)||SpotInside(j)){m.s[i][j]=0LL;continue;}
				bool valid=true;
				for(int row=0;row<3;row++)if(BOTTLE[i][row][2]=='1'&&BOTTLE[j][row][0]=='1')
				{
					valid=false;break;
				}
				m.s[i][j]=(valid?1LL:0LL);
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<N;j++)printf("%d ",m.s[i][j]);puts("");
//		}
		Matrix result=Pow(m,M-1);
		LL ans=0LL;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)(ans+=result.s[i][j])%=MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
