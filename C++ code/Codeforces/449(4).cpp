#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int PHI[1000001];
void BuildPHI()
{
	for(int i=1;i<=1000000;i++)PHI[i]=i;
	for(int i=2;i<=1000000;i++)if(PHI[i]==i)
	{
		for(int j=1;i*j<=1000000;j++)(PHI[i*j]/=i)*=i-1;
	}
}
vector<int>F[1000001];
void BuildF()
{
	for(int i=1;i<=1000000;i++)
	{
		for(int j=1;i*j<=1000000;j++)F[i*j].push_back(i);
	}
}
LL GcdSum(const LL &n)
{
	LL ans=0LL;
	for(const int v:F[n])(ans+=(LL)v*PHI[n/v])%=MOD;
	return ans;
}
LL Solve(const LL &len)
{
	LL ans=(len-1LL)*len;
	if(ans%3LL==0LL)ans=ans/3LL%MOD*(2LL*len-1LL)%MOD;
	else ans=ans%MOD*((2LL*len-1LL)/3LL)%MOD;
	(ans-=len*len)%=MOD;
	(ans+=2LL*GcdSum(len))%=MOD;
	return (ans%MOD+MOD)%MOD;
	return ((len-1LL)*len*(2LL*len-1LL)/3LL-len*len+2LL*GcdSum(len))%MOD;
}
LL N,M;
LL SUM[3][1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPHI();
	BuildF();
	for(int i=0;i<3;i++)SUM[i][0]=0LL;
	for(LL i=1LL;i<=1000000LL;i++)
	{
//		if(i%10000LL==0LL)printf("i=%lld\n",i);
		SUM[0][i]=(SUM[0][i-1]+Solve(i))%MOD;
		SUM[1][i]=(SUM[1][i-1]+i*Solve(i))%MOD;
		SUM[2][i]=(SUM[2][i-1]+i*i%MOD*Solve(i))%MOD;
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%I64d%I64d",&N,&M);
//		for(LL l=1LL;l<=min(N,M);l++)
//		{
//			int ta=(l-1)*l*(2*l-1)/3-l*l+2LL*GcdSum(l);
//			ans+=ta*(N-l+1)*(M-l+1);
//			N*M-N*l+N-M*l+l*l-l+M-l+1
//			N*M+N+M+1-N*l-M*l-l-l+l*l
//		}
		const LL n=min(N,M);
		const LL ans=(N*M+N+M+1LL)%MOD*SUM[0][n]-(N+M+2LL)*SUM[1][n]+SUM[2][n];
		printf("%I64d\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
