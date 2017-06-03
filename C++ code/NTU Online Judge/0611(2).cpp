#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,S,T,M;
vector<pair<int,int> >EDGE;
vector<int>ET[1000];
pair<int,int>Solve()
{
	static pair<int,int>dist[2][1000];
	for(int i=0;i<N;i++)dist[0][i]=dist[1][i]=make_pair(INF,-1);
	queue<pair<int,int> >q;//edge, u
	q.push(make_pair(-1,S)),dist[0][S]=make_pair(0,-1);
	while(!q.empty())
	{
		const auto p=q.front();q.pop();
		for(const int ei:ET[p.second])
		{
			const auto &e=EDGE[ei];
			if(p.first==-1)
			{
				if(p.second==e.first)
				{
					if(dist[0][p.second].first+1<dist[0][e.second].first)
					{
						dist[0][e.second]=make_pair(dist[0][p.second].first+1,-1);
						q.push(make_pair(-1,e.second));
					}
				}
				else
				{
					if(dist[0][p.second].first+1<dist[1][e.first].first)
					{
						dist[1][e.first]=make_pair(dist[0][p.second].first+1,ei);
						q.push(make_pair(ei,e.first));
					}
				}
			}
			else
			{
				if(p.second==e.first)
				{
					if(dist[1][p.second].first+1<dist[1][e.second].first)
					{
						dist[1][e.second]=make_pair(dist[1][p.second].first+1,dist[1][p.second].second);
						q.push(make_pair(dist[1][p.second].second,e.second));
					}
				}
			}
		}
	}
	return min(dist[0][T],dist[1][T]);
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
			ET[a].push_back(i),ET[b].push_back(i);
		}
		const auto &ans=Solve();
		printf("%d %d\n",ans.first,ans.second+1);
	}
	return 0;
}
