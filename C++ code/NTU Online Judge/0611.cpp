#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<utility>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,S,T,M;
vector<pair<int,int> >EDGE;
multiset<int>ET[1000];
int Bfs()
{
	static int dist[1000];
	for(int i=0;i<N;i++)dist[i]=INF;
	queue<int>q;
	q.push(S),dist[S]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int nxt:ET[u])
		{
			if(dist[u]+1<dist[nxt])
			{
				dist[nxt]=dist[u]+1;
				if(nxt==T)return dist[nxt];
				q.push(nxt);
			}
		}
	}
	return INF;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&S,&T),--S,--T;
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		scanf("%d",&M);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			EDGE.push_back(make_pair(a,b));
			ET[a].insert(b);
		}
		int ansd=Bfs(),ansu=-1;
		for(int i=0;i<M;i++)
		{
			const auto &p=EDGE[i];
			ET[p.first].erase(ET[p.first].find(p.second));
			ET[p.second].insert(p.first);
			const int dist=Bfs();
			if(dist<ansd)ansd=dist,ansu=i;
			ET[p.second].erase(ET[p.second].find(p.first));
			ET[p.first].insert(p.second);
		}
		printf("%d %d\n",ansd,ansu+1);
	}
	return 0;
}
