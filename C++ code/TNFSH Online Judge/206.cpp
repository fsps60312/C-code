#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
struct Edge
{
	int a,b,cost;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c),vis(false){}
	int Nxt(const int from)const{return from==a?b:a;}
};
vector<Edge>EDGE;
vector<int>ET[1000000];
int N,L;
struct Pq
{
	int u,cost,precost;
	Pq(){}
	Pq(const int _u,const int _c,const int _p):u(_u),cost(_c),precost(_p){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	static int casenumber;
	while(scanf("%d",&casenumber)==1)
	{
		while(casenumber--)
		{
			scanf("%d%d",&N,&L);
			if(N==1){puts("0");continue;}
			for(int i=0;i<N;i++)ET[i].clear();
			EDGE.clear();
			int nowcost=0;
			for(int i=0,a,b,c;i+1<N;i++)
			{
				scanf("%d%d%d",&a,&b,&c);
				EDGE.push_back(Edge(a,b,c));
				ET[a].push_back(i);
				ET[b].push_back(i);
				nowcost+=c;
			}
			priority_queue<Pq>pq;
			for(int i=0;i<N;i++)if(ET[i].size()==1)
			{
				const int ei=ET[i][0];
				Edge &e=EDGE[ei];
				pq.push(Pq(e.Nxt(i),e.cost,e.cost));
				e.vis=true;
			}
			int ans=0;
			while(!pq.empty()&&nowcost>L)
			{
				const Pq p=pq.top();pq.pop();
				nowcost-=p.precost;
				ans=p.cost;
				for(const auto ei:ET[p.u])if(!EDGE[ei].vis)
				{
					Edge &e=EDGE[ei];
					pq.push(Pq(e.Nxt(p.u),p.cost+e.cost,e.cost));
					e.vis=true;
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
