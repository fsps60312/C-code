#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,M;
vector<int>ET[5000];
void Bfs(const int source,int *dist)
{
	for(int i=0;i<N*2;i++)dist[i]=INF;
	queue<int>q;q.push(source*2),dist[source*2]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<(int)ET[u/2].size();i++)
		{
			const int nxt=ET[u/2][i]*2+((u&1)^1);
			if(dist[nxt]==INF)
			{
				dist[nxt]=dist[u]+1;
				q.push(nxt);
			}
		}
	}
}
int K,DIST[5000][10000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	for(int source=0;source<N;source++)Bfs(source,DIST[source]);
	for(int i=0,s,t,d;i<K;i++)
	{
		scanf("%d%d%d",&s,&t,&d),s--,t--;
		const int ans=DIST[s][t*2+(d&1)];
		puts(!ET[s].empty()&&ans<=d?"TAK":"NIE");
	}
	return 0;
}
