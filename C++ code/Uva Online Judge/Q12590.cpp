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
int N,M,K;
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
void Sub(LL &a,const LL &b){(a-=b)%=MOD;}
void Plus(LL &a,const LL &b){(a+=b)%=MOD;}
LL Solve()
{
	if(N>M)swap(N,M);
	if(N==1)return C(N*M,K);
	const int perimeter=(N+M-2)*2;
	LL ans=C(perimeter,K);
	ans-=2*(C(perimeter-N,K)-C((M-1)*2,K-(N-2)));
	ans-=2*(C(perimeter-M,K)-C((N-1)*2,K-(M-2)));
	ans+=4*(C(N+M-3,K)-C(N-1,K-(M-2))-C(M-1,K-(N-2))+C(1,K-(N-2)-(M-2)));
	ans+=1*C((N-2)*2,K);
	ans+=1*C((M-2)*2,K);
	ans-=2*(C(N-2,K)-C(0,K-(N-2)));
	ans-=2*(C(M-2,K)-C(0,K-(M-2)));
	return (ans%MOD+MOD)%MOD;
}
LL Solve2()
{
	if(N>M)swap(N,M);
	if(N==1)return C(N*M,K);
	const int perimeter=(N+M-2)*2;
	LL ans=C(perimeter,K);
	ans-=2*C(perimeter-N,K);
	ans-=2*C(perimeter-M,K);
	ans+=4*C(N+M-3,K);
	ans+=1*C((N-2)*2,K);
	ans+=1*C((M-2)*2,K);
	ans-=2*C(N-2,K);
	ans-=2*C(M-2,K);
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
