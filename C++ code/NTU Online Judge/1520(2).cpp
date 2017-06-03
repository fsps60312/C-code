#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL MOD,ANS;
struct Trie
{
	int SZ;
	vector<int>CH[10];
	vector<bool>VIS;
	void Clear()
	{
		for(int i=0;i<10;i++)CH[i].clear();
		VIS.clear();
		SZ=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<10;i++)CH[i].push_back(0);
		VIS.push_back(false);
		++SZ;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();
		return CH[c][u]=SZ-1;
	}
	void Insert(LL val)
	{
		vector<int>stk;
		for(;val;val/=10)stk.push_back((int)(val%10));
		int u=0;
		while(!stk.empty())u=GetNxt(u,stk.back()),stk.pop_back();
		assert(!VIS[u]);
		VIS[u]=true;
	}
	void Dfs(const int u,const int depth,LL *dp,LL &ans)
	{
		assert(depth<10);
		if(VIS[u])
		{
			LL ta=1;
			for(int i=0;i<=depth;i++)(ta+=dp[i])%=MOD;
			(ans+=ta)%=MOD;
			(dp[depth]+=ta)%=MOD;
		}
		for(int c=0;c<=9;c++)if(CH[c][u])Dfs(CH[c][u],depth+1,dp,ans);
	}
	LL Solve()
	{
		LL ans=0;
		static LL dp[10];
		for(int i=0;i<10;i++)dp[i]=0;
		for(int c=0;c<=9;c++)if(CH[c][0])Dfs(CH[c][0],0,dp,ans);
		return ans;
	}
}TRIE;
LL A,B;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&A,&B,&MOD)==3)
	{
		if(A==0&&B==0&&MOD==0)break;
		TRIE.Clear();
		for(LL i=A;i<=B;i++)TRIE.Insert(i);
		printf("%lld\n",TRIE.Solve());
	}
	return 0;
}
