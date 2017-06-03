#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,K,PARENT[500000],DEPTH[500000];
vector<int>CYCLE;
void BuildCycle()
{
	static bool vis[500000];
	for(int i=0;i<N;i++)vis[i]=false;
	int cur=0;
	for(;!vis[cur];cur=PARENT[cur])vis[cur]=true;
	CYCLE.clear();
	for(;vis[cur];cur=PARENT[cur])vis[cur]=false,CYCLE.push_back(cur);
	for(int i=0;i<N;i++)DEPTH[i]=1;
	for(int i=0;i<(int)CYCLE.size();i++)PARENT[CYCLE[i]]=CYCLE[i],DEPTH[CYCLE[i]]=0;
}
int Find(const int a)
{
	if(PARENT[a]==a)return a;
	const int parent=PARENT[a];
	PARENT[a]=Find(PARENT[a]);
	DEPTH[a]+=DEPTH[parent];
	return PARENT[a];
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)scanf("%d",&PARENT[i]),PARENT[i]--;
	BuildCycle();
	for(int i=0,a,b;i<K;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		Find(a),Find(b);
		
	}
	return 0;
}
