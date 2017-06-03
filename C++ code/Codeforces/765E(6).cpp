#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
const int INF=0x7fffffff;
int N;
vector<int>ET[200000];
int Solve()
{
	static int d[200000];
	for(int i=0;i<N;i++)d[i]=-1;
	queue<pair<int,int> >q;
	for(int i=0;i<N;i++)if(ET[i].size()==1)
	{
		d[i]=0;q.push(make_pair(i,-1));
	}
	while(!q.empty())
	{
		const auto u=q.front();q.pop();
		for(const int nxt:ET[u.first])if(nxt!=u.second)
		{
			if(d[nxt]==-1)
			{
				d[nxt]=d[u.first]+1;
				q.push(make_pair(nxt,u.first));
			}
			else if(d[nxt]!=d[u.first]+1)
			{
				return -1;
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		printf("%d\n",Solve());
	}
	return 0;
}
