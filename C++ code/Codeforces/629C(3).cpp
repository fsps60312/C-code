#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7; 
int N,M;
char S[100001];
void Check(int &right,int &left)
{
	right=0;
	for(int cnt=0,i=0;i<M;i++)
	{
		if(S[i]=='(')cnt++;
		else if(S[i]==')')cnt--;
		else assert(0);
		if(cnt<0)right++,cnt++;
	}
	left=0;
	for(int cnt=0,i=M-1;i>=0;i--)
	{
		if(S[i]==')')cnt++;
		else if(S[i]=='(')cnt--;
		else assert(0);
		if(cnt<0)left++,cnt++;
	}
}
LL DP[2001][2001];
LL Solve()
{
	int left,right;
	Check(left,right);
	LL ans=0LL;
	for(int i=0;i<=N-M;i++)
	{
		for(int j=0;j+left<=2000&&j+right<=2000;j++)(ans+=DP[i][left+j]*DP[N-M-i][right+j])%=MOD;
	}
	return ans;
}
int main()
{
	for(int i=0;i<=2000;i++)DP[0][i]=0LL;
	DP[0][0]=1LL;
	for(int i=1;i<=2000;i++)
	{
		for(int j=0;j<=2000;j++)DP[i][j]=0LL;
		for(int j=1;j<=2000;j++)(DP[i][j-1]+=DP[i-1][j])%=MOD;
		for(int j=0;j<2000;j++)(DP[i][j+1]+=DP[i-1][j])%=MOD;
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
