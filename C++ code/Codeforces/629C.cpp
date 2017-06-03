#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7; 
int N,M;
char S[100001];
LL DP[2001];
int Check()
{
	int i=0;
	while(i<M&&S[i]==')')i++;
	for(int cnt=0;i<M;i++)
	{
		if(S[i]=='(')cnt++;
		else if(S[i]==')')cnt--;
		else assert(0);
		if(cnt<0)return -1;
	}
	i=M-1;
	while(i>=0&&S[i]=='(')i--;
	for(int cnt=0;i>=0;i--)
	{
		if(S[i]==')')cnt++;
		else if(S[i]=='(')cnt--;
		else assert(0);
		if(cnt<0)return -1;
	}
	int cnt=0;
	for(int i=0;i<M;i++)
	{
		if(S[i]=='(')cnt++;
		else if(S[i]==')')cnt--;
		else assert(0);
	}
	return abs(cnt);
}
LL Solve()
{
	const int dif=Check();
	if(dif==-1||dif>N-M)return 0LL;
	if(dif==0)return DP[N-M]*(N-M+1LL);
	LL ans=0LL;
	for(int i=0;i+dif<=N-M;i+=2)(ans+=dif*DP[i]%MOD*DP[N-(M+i+dif)]%MOD*(N-(M+i+dif)+1LL))%=MOD;
	return ans;
}
int main()
{
	for(int i=0;i<=2000;i++)DP[i]=0LL;
	DP[0]=1LL;
	for(int i=2;i<=2000;i+=2)
	{
		LL &ans=DP[i]=0LL;
		for(int j=0;j<i;j+=2)(ans+=DP[j]*DP[i-2-j])%=MOD;
	}
//	for(int i=0;i<=10;i++)printf("%lld\n",DP[i]);
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		scanf("%s",S);
		printf("%I64d\n",Solve());
	}
	return 0;
}
