#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
int N;
vector<int>ET[100000];
int PRE[100000],LOW[100000],SCC[100000],PRE_CNT,SCC_CNT;
stack<int>STK;
void Dfs(const int u)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(!PRE[nxt])
		{
			Dfs(nxt);
			LOW[u]=min(LOW[u],LOW[nxt]);
		}
		else if(SCC[nxt]==-1)LOW[u]=min(LOW[u],PRE[nxt]);
	}
	if(PRE[u]==LOW[u])
	{
		while(STK.top()!=u)
		{
			SCC[STK.top()]=SCC_CNT;
			STK.pop();
		}
		SCC[u]=SCC_CNT++;
		STK.pop();
	}
}
vector<int>EA[100000];
int IN[100000];
LL SCC_SZ[100000];
bool ANS[100000];
void Solve()
{
	for(int i=0;i<SCC_CNT;i++)EA[i].clear(),SCC_SZ[i]=0LL,IN[i]=0;
	for(int i=0;i<N;i++)
	{
		SCC_SZ[SCC[i]]++;
		for(int j=0;j<ET[i].size();j++)
		{
			if(SCC[i]==SCC[ET[i][j]])continue;
			EA[SCC[i]].push_back(SCC[ET[i][j]]);
			IN[SCC[ET[i][j]]]++;
		}
	}
	for(int i=0;i<SCC_CNT;i++)ANS[i]=false;
	queue<int>q;
	for(int i=0;i<SCC_CNT;i++)if(IN[i]==0)ANS[i]=true,q.push(i);
	assert(!q.empty());
	for(int i=0;i<SCC_CNT;i++)printf("SCC[%d]=%d\n",i,SCC[i]);
//	puts("a");
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		printf("u=%d\n",u);
		sort(EA[u].begin(),EA[u].end());
		for(int l=0;l<EA[u].size();)
		{
			const int nxt=EA[u][l];
			int r=l;
			while(r<EA[u].size()&&EA[u][r]==nxt)r++;
			assert((LL)(r-l)<=SCC_SZ[u]*SCC_SZ[nxt]);
			if((LL)(r-l)<SCC_SZ[u]*SCC_SZ[nxt]&&!ANS[nxt])
			{
				ANS[nxt]=true;
				q.push(nxt);
			}
			l=r;
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		static int cnt;scanf("%d",&cnt);
		while(cnt--)
		{
			static int v;scanf("%d",&v);
			v--;ET[i].push_back(v);
		}
	}
	for(int i=0;i<N;i++)PRE[i]=0,SCC[i]=-1;
	PRE_CNT=SCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i);
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[SCC[i]])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[SCC[i]])printf(" %d",i+1);
	puts("");
	return 0;
}
