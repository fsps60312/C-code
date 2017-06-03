#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7; 
int N,M;
char S[100001];
LL DP[2001];
bool Check(int &right,int &left)
{
	int i=0;
	while(i<M&&S[i]==')')i++;
	for(int &cnt=right=0;i<M;i++)
	{
		if(S[i]=='(')cnt++;
		else if(S[i]==')')cnt--;
		else assert(0);
		if(cnt<0)return false;
	}
	i=M-1;
	while(i>=0&&S[i]=='(')i--;
	for(int &cnt=left=0;i>=0;i--)
	{
		if(S[i]==')')cnt++;
		else if(S[i]=='(')cnt--;
		else assert(0);
		if(cnt<0)return false;
	}
	return true;
}
LL GetLeft(const int left,const int free)
{
	if(left==0)return free==0?1:0;
	return left*DP[free]%MOD;
}
LL Solve()
{
	int left,right;
	if(!Check(left,right)||left+right>N-M)return 0LL;
	LL ans=0LL;
	for(int i=0;i+left+right<=N-M;i+=2)for(int j=0;i+j+left+right<=N-M;j+=2)
	{
		const int remain=N-M-(left+right+i+j);
		(ans+=GetLeft(left,i)*GetLeft(right,j)%MOD*(DP[remain]*(remain+1LL))%MOD)%=MOD;
	}
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
		printf("%lld\n",Solve());
	}
	return 0;
}
