#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL C[100001][101];
void BuildC()
{
	C[0][0]=1LL;
	for(int i=1;i<=100000;i++)
	{
		C[i][0]=1LL;
		for(int j=1;j<=100&&j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		if(i<=100)C[i][i]=1LL;
	}
}
int N,M;
LL A[100000],DIF[102][100000];
void Modify(const int loc,const int n,const int k,const LL sign)
{
	for(int i=0;i<=k&&loc+i<N;i++)
	{
		(DIF[i+1][loc+i]+=sign*C[n][k-i])%=MOD;
//		printf("Add(%d,%d):%lld\n",i+1,loc+i,sign*C[n][k-i]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	BuildC();
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%lld",&A[i]);
		DIF[0][0]=0;
		for(int i=0;i<N;i++)DIF[0][i]=A[i];
		for(int dep=1;dep<=101;dep++)
		{
			for(int i=dep-1;i<N;i++)DIF[dep][i]=0LL;
		}
		for(int l,r,k;M--;)
		{
			scanf("%d%d%d",&l,&r,&k),l--,r--;
			Modify(l,k,k,1LL);
			Modify(r+1,k+(r-l+1),k,-1LL);
		}
		for(int dep=101;dep>=1;dep--)
		{
			LL sum=0LL;
			for(int i=dep-1;i<N;i++)
			{
				(sum+=DIF[dep][i])%=MOD;
				(DIF[dep-1][i]+=sum)%=MOD;
			}
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%lld",(DIF[0][i]+MOD)%MOD);
		}
		puts("");
	}
	return 0;
}
