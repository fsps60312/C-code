#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
vector<int> TO[1001];
int T,N,S,K,VIS[1001],FA[1001];
struct Bfs
{
	int u, dep;
	Bfs(int _u,int d):u(_u),dep(d){}
};
vector<Bfs> LEAF;
bool cmpLEAF(Bfs a,Bfs b){return a.dep>b.dep;}
int getmin(int &a,int b){if(b<a)a=b;}
void dfs(int u,int fa,int dep)
{
	FA[u]=fa;
	int leaf=1;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(j==fa)continue;
		leaf=0;
		dfs(j,u,dep+1);
	}
	VIS[u]=dep<=K?1:0;
	if(leaf&&dep>K)
	{
		LEAF.push_back(Bfs(u,dep));
	}
}
int solve()
{
	dfs(S,-1,0);
	sort(LEAF.begin(),LEAF.end(),cmpLEAF);
	int ans=0;
	for(int i=0;i<LEAF.size();i++)
	{
		if(VIS[LEAF[i].u])continue;
		int u=LEAF[i].u;
		for(int j=0;j<K;j++)u=FA[u];
		queue<Bfs> q;
		q.push(Bfs(u,0));
		while(!q.empty())
		{
			Bfs b=q.front();q.pop();
			if(b.dep>K)break;
			if(VIS[b.u]==i+2)continue;
			VIS[b.u]=i+2;
			for(int j=0;j<TO[b.u].size();j++)
			{
				q.push(Bfs(TO[b.u][j],b.dep+1));
			}
		}
		ans++;
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&S,&K);
		LEAF.clear();
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
		}
		for(int i=1;i<N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
			TO[b].push_back(a);
		}
		printf("%d\n",solve());
	}
	return 0;
}
