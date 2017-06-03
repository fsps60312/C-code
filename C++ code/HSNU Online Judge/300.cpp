#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int N,M,A[100000];
vector<int>ET[100000];
vector<int>CYC;
void BuildCYC()
{
	static bool vis[100000];
	for(int i=0;i<N;i++)vis[i]=false;
	queue<int>q;
	if(true)
	{
		int cur=0;
		for(;!vis[cur];cur=A[cur])q.push(cur),vis[cur]=true;
		while(q.front()!=cur)q.pop();
	}
	CYC.clear();
	while(!q.empty())CYC.push_back(q.front()),q.pop();
	M=CYC.size();
}
LL GetValue_DP[100000][2];
LL GetValue(const int u,const int color)
{
	LL &ans=GetValue_DP[u][color];
	if(ans!=-1LL)return ans;
	ans=1LL;
	for(const int nxt:ET[u])
	{
		const LL ta=GetValue(nxt,0)+(color?0LL:GetValue(nxt,1));
		(ans*=ta)%=MOD;
	}
	return ans;
}
LL DP[100000][2][2];
LL Solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<2;j++)GetValue_DP[i][j]=-1LL;
	for(int i=0;i<M;i++)for(int j=0;j<4;j++)DP[i][j>>1][j&1]=0LL;
	DP[0][0][0]=GetValue(CYC[0],0);
	DP[0][1][1]=GetValue(CYC[0],1);
	for(int i=0;i+1<M;i++)
	{
		for(int l=0;l<2;l++)for(int r=0;r<2;r++)if(DP[i][l][r]!=0LL)
		{
			const LL &dp=DP[i][l][r];
			assert(dp>=0LL&&dp<MOD);
			(DP[i+1][l][0]+=dp*GetValue(CYC[i+1],0))%=MOD;
			if(r==0)(DP[i+1][l][1]+=dp*GetValue(CYC[i+1],1))%=MOD;
		}
	}
	return (DP[M-1][0][0]+DP[M-1][0][1]+DP[M-1][1][0])%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&A[i]),ET[--A[i]].push_back(i);
		BuildCYC();
		for(int i=0;i<M;i++)
		{
			vector<int>&s=ET[CYC[(i+1)%M]];
			bool found=false;
			for(auto t=s.begin();t!=s.end();t++)if(*t==CYC[i]){s.erase(t),found=true;break;}
			assert(found);
		}
		const LL ans=Solve();
		assert(ans>=0LL&&ans<MOD);
		printf("%lld\n",ans);
	}
	return 0;
}
