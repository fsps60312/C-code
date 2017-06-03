#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL C_DP[10001][101];
LL C(const int a,const int b)
{
	assert(a>=0);
	if(b<0||a<b)return 0LL;
	LL &ans=C_DP[a][b];
	if(ans!=-1LL)return ans;
	if(b==0LL||b==a)return ans=1LL;
	ans=(C(a-1,b-1)+C(a-1,b))%MOD;
//	printf("C(%d,%d)=%lld\n",a,b,ans);
	return ans;
}
LL Cover0_DP[101][101][101];
LL Cover0(const int N,const int M,const int K)
{
	if(K<0)return 0LL;
	LL &ans=Cover0_DP[N][M][K];
	if(ans!=-1LL)return ans;
	ans=0LL;
	for(int blank=0;blank<=M;blank++)
	{
		const LL v=(C(M,blank)*C((M-blank)*N,K))%MOD;
		if(blank%2==0)ans+=v;
		else ans-=v;
	}
//	printf("Cover0(%d,%d,%d)=%lld\n",N,M,K,ans);
	return ans=(ans%MOD+MOD)%MOD;
}
LL Cover1_DP[101][101][101];
LL Cover1(const int N,const int M,const int K)
{
	if(K<0)return 0LL;
	LL &ans=Cover1_DP[N][M][K];
	if(ans!=-1LL)return ans;
	ans=Cover0(N,M,K);
	for(int cnt=1;cnt<=N;cnt++)ans-=C(N-1,cnt-1)*Cover0(N,M-1,K-cnt)%MOD;
//	printf("Cover1(%d,%d,%d)=%lld\n",N,M,K,ans);
	return ans=(ans%MOD+MOD)%MOD;
}
LL Cover2_DP[101][101][101];
LL Cover2(const int N,const int M,const int K)
{
	if(K<0)return 0LL;
	LL &ans=Cover2_DP[N][M][K];
	if(ans!=-1LL)return ans;
	ans=Cover1(N,M,K);
	for(int cnt=1;cnt<=N;cnt++)ans-=C(N-1,cnt-1)*Cover1(N,M-1,K-cnt)%MOD;
//	printf("Cover2(%d,%d,%d)=%lld\n",N,M,K,ans);
	return ans=(ans%MOD+MOD)%MOD;
}
LL Solve0(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M+N*M,K);
	a-=2LL*C(N+M+N+N*M,K);
	a-=2LL*C(M+N+M+N*M,K);
	a+=4LL*C(N+M+N*M,K);
	a+=1LL*C(N+N+N*M,K);
	a+=1LL*C(M+M+N*M,K);
	a-=2LL*C(N+N*M,K);
	a-=2LL*C(M+N*M,K);
	a+=1LL*C(N*M,K);
//	printf("a=%lld,(%lld,%lld)\n",a,Cover2(N+1,M+2,K),Cover0(N,M+2,K));
	a+=2LL*Cover2(N+1,M+2,K)-Cover0(N,M+2,K);
//	printf("a=%lld\n",a);
	a+=2LL*Cover2(M+1,N+2,K)-Cover0(M,N+2,K);
//	printf("a=%lld\n",a);
	return (a%MOD+MOD)%MOD;
}
LL Solve1(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M+N*M,K);
	a-=C(N+M+N+N*M,K);
	a-=C(M+N+M+N*M,K);
	a+=C(N+M+N*M,K);
	a+=Cover2(N+1,M+2,K)+Cover1(N+1,M+1,K);
	a+=Cover2(M+1,N+2,K)+Cover1(M+1,N+1,K);
	return (a%MOD+MOD)%MOD;
}
LL Solve2(const int N,const int M,const int K)
{
	LL a=C(N+M+N+M+N*M,K);
	a-=C(N+M+N+N*M,K);
	a+=Cover2(N+1,M+2,K)+2LL*Cover1(N+1,M+1,K)+Cover0(N+1,M,K);
	return (a%MOD+MOD)%MOD;
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
	(ans+=2LL*C(N+M+N+M+N*M,K-2))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=4LL*C(N+M+N+M+N*M,K-3))%=MOD;
//	printf("ans=%lld\n",ans);
	(ans+=1LL*C(N+M+N+M+N*M,K-4))%=MOD;
//	printf("ans=%lld\n",ans);
	return (ans%MOD+MOD)%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<=10000;i++)for(int j=0;j<=100;j++)C_DP[i][j]=-1LL;
	for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)for(int k=0;k<=100;k++)Cover0_DP[i][j][k]=Cover1_DP[i][j][k]=Cover2_DP[i][j][k]=-1LL;
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d",&N,&M,&K);
		static int kase=1;
		printf("Case %d: %lld\n",kase++,Solve());
	}
	return 0;
}
