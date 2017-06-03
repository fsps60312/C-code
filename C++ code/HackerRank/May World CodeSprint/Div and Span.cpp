#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL LEVEL[200002],REVLV[200002];
void ExGcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1LL);x=1LL,y=0LL;return;}
	ExGcd(b,a%b,y,x);
	(y-=a/b*x)%=MOD;
}
LL Rev(const LL a)
{
	LL x,y;
	ExGcd(a,MOD,x,y);
	return (x%MOD+MOD)%MOD;
}
LL C(const int a,const int b)
{
	if(b>a)return 0LL;
	return LEVEL[a]*REVLV[b]%MOD*REVLV[a-b]%MOD;
}
LL CATALAN[100001];
LL DP[201][201];
LL Solve(const int X,const int Y)
{
	LL ans=0LL;
	for(int g=1;g<=Y;g++)
	{
		(ans+=CATALAN[X]*C(2*X+1,g)%MOD*DP[g][Y]%MOD)%=MOD;
	}
	return ans*LEVEL[X]%MOD*LEVEL[Y]%MOD;
}
int main()
{
	LEVEL[0]=1LL;
	for(LL i=1LL;i<=200001LL;i++)LEVEL[i]=(LEVEL[i-1]*i)%MOD;
	for(int i=0;i<=200001;i++)REVLV[i]=Rev(LEVEL[i]);
	for(int i=1;i<=100000;i++)CATALAN[i]=(C(2*i,i)-C(2*i,i+1)+MOD)%MOD;
	for(int i=0;i<=200;i++)for(int j=0;j<=200;j++)DP[i][j]=0LL;
	DP[0][0]=1LL;
	for(int cnt=0;cnt<200;cnt++)for(int sum=0;sum<200;sum++)
	{
		for(int add=1;sum+add<=200;add++)(DP[cnt+1][sum+add]+=DP[cnt][sum]*CATALAN[add])%=MOD;
	}
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int x,y;testcount--;)
	{
		scanf("%d%d",&x,&y);
		printf("%lld\n",Solve(x,y));
	}
	return 0;
}
