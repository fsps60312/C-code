#include<cstdio>
#include<cassert>
using namespace std;
const int MOD=1000000007;
int N;
char S[5001];
int DP[5000][5000];
bool Smaller(const int l,const int r)
{
	for(int i=0;l+i<=r;i++)
	{
		if(S[l+i]!=S[r+1+i])return S[l+i]<S[r+1+i];
	}
	return false;
}
int GetDP(const int l,const int r)
{
	int &dp=DP[l][r];
	if(dp!=-1)return dp;
	if(S[l]=='0')return dp=0;
	if(r==N-1)return dp=1;
	int end;
	if(Smaller(l,r))end=r+(r-l+1);
	else end=r+(r-l+2);
	dp=0;
	while(end<N)(dp+=GetDP(r+1,end))%=MOD,end++;
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		for(int i=0;i<N;i++)for(int j=i;j<N;j++)DP[i][j]=-1;
		int ans=0;
		for(int i=0;i<N;i++)(ans+=GetDP(0,i))%=MOD;
		printf("%d\n",ans);
		break;
	}
	return 0;
}
