#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
void ExGcd(const LL &a,const LL &b,LL &x,LL &y)
{
	if(b==0LL){x=1LL,y=0LL;return;}
	ExGcd(b,a%b,y,x);
	//by+(a-a/b*b)x==g
	//ax+b(y-a/b*x)==g
	(y-=a/b*x)%=MOD;
}
LL INV[397],C_BASE[397][397];
LL C(const int a,const int b)
{
	assert(a>=0);
	if(b>a||b<0)return 0LL;
	LL &ans=C_BASE[a][b];
	if(ans!=-1LL)return ans;
	ans=1LL;
	for(int i=b+1;i<=a;i++)
	{
		(ans*=i)%=MOD;
		(ans*=INV[i-b])%=MOD;
	}
	return ans;
}
LL Solve0(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M,K);
	a-=2LL*C(N+M+N,K);
	a-=2LL*C(M+N+M,K);
	a+=4LL*C(N+M,K);
	a+=1LL*C(N+N,K);
	a+=1LL*C(M+M,K);
	a-=2LL*C(N,K);
	a-=2LL*C(M,K);
	a+=2LL*(C(N+N,K-M)-2LL*C(N,K-M)+C(0,K-M));
	a+=2LL*(C(M+M,K-N)-2LL*C(M,K-N)+C(0,K-M));
	return a;
}
LL Solve1(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M,K);
	a-=C(N+M+N,K);
	a-=C(M+N+M,K);
	a+=C(N+M,K);
	a+=C(N+N,K-M)-C(N,K-M);
	a+=C(M+M,K-N)-C(M,K-N);
	return a;
}
LL Solve2(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M,K);
	a-=C(N+M+N,K);
	a+=C(N+N,K-M);
//	printf("a=%lld\n",a);
	return a;
}
int N,M,K;
LL Solve()
{
	if(N>M)swap(N,M);
	if(N==1)return C(N*M,K);
	N-=2,M-=2;
	LL ans=Solve0(N,M,K);
//	printf("ans=%lld\n",ans);
	(ans+=4LL*Solve1(N,M,K-1))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=2LL*Solve2(N,M,K-2))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=2LL*Solve2(M,N,K-2))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=2LL*C(N+M+N+M,K-2))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=4LL*C(N+M+N+M,K-3))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=1LL*C(N+M+N+M,K-4))%=MOD;
//	printf("ans=%lld\n",ans);
	return (ans%MOD+MOD)%MOD;
}
int main()
{
	for(int i=1;i<=396;i++)
	{
		static LL x,y;
		ExGcd(i,MOD,x,y);
		INV[i]=(x%MOD+MOD)%MOD;
	}
	for(int i=0;i<=396;i++)for(int j=0;j<=396;j++)C_BASE[i][j]=-1LL;
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d",&N,&M,&K);
		static int kase=1;
		printf("Case %d: %lld\n",kase++,Solve());
	}
	return 0;
}
