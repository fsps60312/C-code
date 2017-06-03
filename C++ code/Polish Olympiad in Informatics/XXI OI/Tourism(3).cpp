#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
int N,M;
vector<int>ET[20000];
int C[20000],DEPTH[20000];
void BuildDepth(const int u,const int depth)
{
	assert(DEPTH[u]==-1);
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==-1)BuildDepth(nxt,depth+1);
	}
}
inline void Add(int &a,const int b)
{
	if(a==INF||b==INF){a=INF;return;}
	a+=b;
}
//typedef long long LL;
void GetDP(const int u,int *dp)
{
	vector<int*>ch_dps;
	vector<int>parents;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==DEPTH[u]+1)
		{
			int *ch_dp=new int[1<<DEPTH[nxt]];
			printf("%d->%d\n",u+1,nxt+1);
			GetDP(nxt,ch_dp);
			ch_dps.push_back(ch_dp);
		}
		else if(DEPTH[nxt]<DEPTH[u])parents.push_back(nxt);
	}
	for(int s=0;s<(1<<DEPTH[u]);s++)dp[s]=INF;
	for(int s=0;s<(1<<DEPTH[u]);s++)
	{
		bool covered_by_parents=false;
		for(int i=0;i<(int)parents.size();i++)if(s&(1<<DEPTH[parents[i]])){covered_by_parents=true;break;}
		if(!covered_by_parents)
		{
			int cost=C[u];
			for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s]);
			int nxts=s;
			for(int i=0;i<(int)parents.size();i++)nxts|=1<<DEPTH[parents[i]];
			getmin(dp[nxts],cost);
		}
		else
		{
			int cost=0;
			for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s+(1<<DEPTH[u])]);
			getmin(dp[s],cost);
		}
		if(true)
		{
			int cost=C[u];
			for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s+(1<<DEPTH[u])]);
			int nxts=s;
			for(int i=0;i<(int)parents.size();i++)nxts|=1<<DEPTH[parents[i]];
			getmin(dp[nxts],cost);
		}
	}
	for(int i=0;i<(int)ch_dps.size();i++)delete[]ch_dps[i];
	vector<int*>().swap(ch_dps);
	vector<int>().swap(parents);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)DEPTH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)if(DEPTH[i]==-1)
		{
			puts("a");
			BuildDepth(i,0);
			puts("b");
			int *dp=new int[1];
			GetDP(i,dp);
			Add(ans,dp[0]);
		}
		printf("%d\n",ans);
		assert(ans!=INF);
	}
	return 0;
}
