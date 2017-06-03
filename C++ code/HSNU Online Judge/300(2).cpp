#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int DJ[100000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int N,M,A[100000];
vector<int>ET[100000];
vector<int>CYC;
bool VIS[100000];
void BuildCYC(const int source)
{
	queue<int>q;
	if(true)
	{
		int cur=source;
		for(;!VIS[cur];cur=A[cur])q.push(cur),VIS[cur]=true;
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
LL Solve(const vector<int>&cyc)
{
	static LL dp[100000][2][2];
	for(int i=0;i<M;i++)for(int j=0;j<4;j++)dp[i][j>>1][j&1]=0LL;
	dp[0][0][0]=GetValue(cyc[0],0);
	dp[0][1][1]=GetValue(cyc[0],1);
	for(int i=0;i+1<M;i++)
	{
		for(int l=0;l<2;l++)for(int r=0;r<2;r++)if(dp[i][l][r]!=0LL)
		{
			const LL &v=dp[i][l][r];
			(dp[i+1][l][0]+=v*GetValue(cyc[i+1],0))%=MOD;
			if(r==0)(dp[i+1][l][1]+=v*GetValue(cyc[i+1],1))%=MOD;
		}
	}
	return (dp[M-1][0][0]+dp[M-1][0][1]+dp[M-1][1][0])%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear(),DJ[i]=i;
		for(int i=0;i<N;i++)scanf("%d",&A[i]),ET[--A[i]].push_back(i),DJ[Find(A[i])]=Find(i);
		for(int i=0;i<N;i++)for(int j=0;j<2;j++)GetValue_DP[i][j]=-1LL;
		static bool vis[100000];
		for(int i=0;i<N;i++)vis[i]=VIS[i]=false;
		LL ans=1LL;
		for(int i=0;i<N;i++)if(!vis[Find(i)])
		{
			vis[Find(i)]=true;
			BuildCYC(i);
			for(int i=0;i<M;i++)
			{
				vector<int>&s=ET[CYC[(i+1)%M]];
				bool found=false;
				for(auto t=s.begin();t!=s.end();t++)if(*t==CYC[i]){s.erase(t),found=true;break;}
				assert(found);
			}
			(ans*=Solve(CYC))%=MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
