#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
int N,Q,PARENT[300000];
vector<int>ET[300000],TOPU;
LL K,COST[300001],TAG[300001];
int ANS[300000];
pair<int,LL>QUERY[300000];
int DJ[300001];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
//	freopen("s1.in","r",stdin);
	while(scanf("%d%d%lld",&N,&Q,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,v;i<N;i++)scanf("%d",&v),ET[PARENT[i]=--v].push_back(i);
		PARENT[0]=N;
		for(int i=0;i<N;i++)COST[i]=TAG[i]=0LL;
		for(int i=0;i<Q;i++)
		{
			auto &q=QUERY[i];
			scanf("%d%lld",&q.first,&q.second),COST[--q.first]+=q.second;
		}
		if(true)
		{
			TOPU.clear();
			queue<int>q;q.push(0);
			while(!q.empty())
			{
				const int u=q.front();q.pop();
				TOPU.push_back(u);
				for(const int nxt:ET[u])q.push(nxt);
			}
			assert((int)TOPU.size()==N);
		}
		for(int i=N-1;i>=0;i--)
		{
			const int u=TOPU[i];
			for(const int nxt:ET[u])COST[u]+=COST[nxt];
		}
		for(int i=0;i<=N;i++)DJ[i]=i;
		int ans=N;
		for(int i=N-1;i>=0;i--)
		{
			const int u=TOPU[i];
			if(COST[u]<K)DJ[u]=PARENT[u],ans--;
		}
		for(int i=Q-1;i>=0;i--)
		{
			ANS[i]=ans;
			const auto &q=QUERY[i];
			int u=Find(q.first);
			TAG[u]+=q.second;
			COST[u]-=q.second;
			while(u!=N&&COST[u]<K)
			{
				const int nxt=Find(PARENT[u]);
				TAG[nxt]+=TAG[u];
				COST[nxt]-=TAG[u];
				u=DJ[u]=nxt,ans--;
			}
		}
		for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
