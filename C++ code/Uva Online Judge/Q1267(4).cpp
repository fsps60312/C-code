#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
vector<int> TO[1001];
int T,N,S,K,VIS[1001],FA[1001],LEAF[1001];
int getmin(int &a,int b){if(b<a)a=b;}
struct Bfs
{
	int u, dep;
	Bfs(int _u,int d):u(_u),dep(d){}
};
void dfs(int u,int fa)
{
	FA[u]=fa;
	int &leaf=LEAF[u]=1;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(j==fa)continue;
		leaf=0;
		dfs(j,u);
	}
}
int solve()
{
	dfs(S,-1);
	int ans=-1;
	queue<Bfs> q;
	vector<int> serve;
	Bfs last=Bfs(S,K+1);
	while(last.dep>K)
	{
		last.dep=0;
		for(int i=1;i<=N;i++)VIS[i]=0;
		if(last.u!=S)
		{
			for(int i=0;i<K;i++)
			{
				last.u=FA[last.u];
			}
		}
		serve.push_back(last.u);
		for(int i=0;i<serve.size();i++)q.push(Bfs(serve[i],0));
		while(!q.empty())
		{
			Bfs b=q.front();q.pop();
			if(VIS[b.u])continue;
			VIS[b.u]=1;
			for(int i=0;i<TO[b.u].size();i++)
			{
				q.push(Bfs(TO[b.u][i],b.dep+1));
			}
			if(LEAF[b.u])last=b;
		}
		ans++;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&S,&K);
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
