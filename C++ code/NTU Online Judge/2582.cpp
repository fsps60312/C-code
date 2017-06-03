#include<cstdio>
#include<cassert>
#include<queue>
#include<map>
using namespace std;
struct Edge
{
	int A,B,COST;
	bool VIS;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST),VIS(false){}
};
//bool operator<(const Edge &a,const Edge &b){return a.COST<b.COST;}
int N,M;
vector<Edge>EDGE;
vector<int>ET[100000];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		queue<int>q;
		q.push(0);
		int ans=0;
		multimap<pair<int,int>,int>s;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const int ei:ET[u])
			{
				EDGE[ei].VIS^=true;
				const Edge &e=EDGE[ei];
				if(e.VIS)
				{
					const int nxt=(u==e.A?e.B:e.A);
					s.insert(make_pair(make_pair(e.COST,ei),nxt));
				}
				else
				{
					s.erase(make_pair(e.COST,ei));
				}
			}
			if(s.empty())break;
			ans+=s.rbegin()->first.first-s.begin()->first.first;
			q.push(s.rbegin()->second);
		}
		assert(q.empty());
		printf("%d\n",ans);
	}
	return 0;
}
