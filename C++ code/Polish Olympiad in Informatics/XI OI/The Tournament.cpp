#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
vector<int>ET[100000];
int PRE[100000],SCC[100000],PRE_CNT,SCC_CNT;
stack<int>STK;
int Dfs(const int u,const int parent)
{
	int low=PRE[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		if(!PRE[nxt])getmin(low,Dfs(nxt,u));
		else if(SCC[nxt]==-1)getmin(low,PRE[nxt]);
	}
	if(low==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			SCC[v]=SCC_CNT;
			if(v==u)break;
		}
		SCC_CNT++;
	}
	return low;
}
int N;
void RebuildGraph()
{
	static vector<int>et_ans[100000];
	for(int i=0;i<N;i++)for(const int nxt:ET[i])
	{
		if(SCC[i]!=SCC[nxt])et_ans[SCC[i]].push_back(SCC[nxt]);
	}
	for(int i=0;i<SCC_CNT;i++)sort(et_ans[i].begin(),et_ans[i].end());
	for(int i=0;i<N;i++)ET[i].swap(et_ans[i]),vector<int>().swap(et_ans[i]);
}
void FindWinners(vector<int>&output)
{
	int *degree_in=new int[SCC_CNT],*scc_size=new int[SCC_CNT];
	for(int i=0;i<SCC_CNT;i++)degree_in[i]=scc_size[i]=0;
	for(int i=0;i<N;i++)scc_size[SCC[i]]++;
	for(int i=0;i<SCC_CNT;i++)for(const int nxt:ET[i])degree_in[nxt]++;
	queue<int>scc_win;
	set<int>unknown;
	for(int i=0;i<SCC_CNT;i++)
	{
		if(degree_in[i]==0)scc_win.push(i);
		else unknown.insert(i);
	}
	delete[]degree_in;
	output.clear();
	while(!scc_win.empty())
	{
		const int u=scc_win.front();scc_win.pop();
		output.push_back(u);
		for(auto nxt=unknown.begin();nxt!=unknown.end();)
		{
			const int edge_count=upper_bound(ET[u].begin(),ET[u].end(),*nxt)-lower_bound(ET[u].begin(),ET[u].end(),*nxt);
			if(edge_count<(long long)scc_size[u]*scc_size[*nxt])
			{
				scc_win.push(*nxt);
				unknown.erase(nxt++);
			}
			else nxt++;
		}
	}
	delete[]scc_size;
	bool *is_win=new bool[SCC_CNT];
	for(int i=0;i<SCC_CNT;i++)is_win[i]=false;
	for(const int v:output)is_win[v]=true;
	output.clear();
	for(int i=0;i<N;i++)if(is_win[SCC[i]])output.push_back(i);
	delete[]is_win;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0,k;i<N;i++)
	{
		ET[i].clear();
		scanf("%d",&k);
		for(int v;k--;)scanf("%d",&v),ET[i].push_back(--v);
	}
	for(int i=0;i<N;i++)PRE[i]=0,SCC[i]=-1;
	PRE_CNT=SCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),assert(STK.empty());
	RebuildGraph();
	vector<int>ans;
	FindWinners(ans);
	printf("%d",(int)ans.size());
	for(const int v:ans)printf(" %d",v+1);
	puts("");
	return 0;
}
