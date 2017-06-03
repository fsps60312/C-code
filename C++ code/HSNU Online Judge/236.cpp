#include<cstdio>
typedef long long LL;
const LL INF=9223372036854775807LL;
LL N,A,B,C,S[1000001],SUM[1000001],DP[1000001];
LL Sum(const LL &l,const LL &r){return SUM[r]-SUM[l-1];}
LL Sq(const LL &v){return v*v;}
void getmax(LL &a,const LL &b){if(b>a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld%lld%lld%lld",&N,&A,&B,&C);
	for(LL i=1LL;i<=N;i++)scanf("%lld",&S[i]);
	DP[0]=SUM[0]=0LL;
	for(LL i=1LL;i<=N;i++)DP[i]=-INF,SUM[i]=SUM[i-1LL]+S[i];
	for(LL i=1LL;i<=N;i++)
	{
		for(LL j=1LL;j<=i;j++)getmax(DP[i],DP[j-1LL]+A*Sq(Sum(j,i))+C);
	}
	printf("%lld\n",DP[N]+SUM[N]*B);
	return 0;
}
