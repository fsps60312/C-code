#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Edge
{
	int end[2];
	int d;
	Edge(){}
	Edge(const int _a,const int _b,const int _d):end{_a,_b},d(_d){}
};
vector<Edge>EDGE;
vector<int>ET[2000],EF[2000];
int VIS[2000],VIS_CNT;
bool DfsTo(const int u,const int target)
{
	if(VIS[u])return VIS[u]<VIS_CNT;
	VIS[u]=VIS_CNT;
	if(u==target){VIS_CNT++;return true;}
	for(const int ei:ET[u])
	{
		Edge &e=EDGE[ei];
		const int pred=e.d;
		if(e.d==-1)e.d=(u==e.end[0]?1:0);
		const int nxt=e.end[e.d];
		if(DfsTo(nxt,target))return true;
		else e.d=pred;
	}
	VIS[u]=0;
	return false;
}
bool DfsFrom(const int u)
{
	if(VIS[u])return VIS[u]<VIS_CNT;
	VIS[u]=VIS_CNT;
	for(const int ei:EF[u])
	{
		Edge &e=EDGE[ei];
		const int pred=e.d;
		if(e.d==-1)e.d=(u==e.end[0]?0:1);
		const int nxt=e.end[e.d^1];
		if(DfsFrom(nxt))return true;
		else e.d=pred;
	}
	VIS[u]=0;
	return false;
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear(),VIS[i]=0;
		VIS_CNT=0;
		EDGE.clear();
		vector<int>twowayroad;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			if(c==1)
			{
				EDGE.push_back(Edge(a,b,1));
				ET[a].push_back(i);
				EF[b].push_back(i);
			}
			else if(c==2)
			{
				EDGE.push_back(Edge(a,b,-1));
				ET[a].push_back(i),ET[b].push_back(i);
				EF[b].push_back(i),EF[a].push_back(i);
				twowayroad.push_back(i);
			}
			else assert(0);
		}
		for(const Edge &e:EDGE)if(e.d==1)
		{
			VIS_CNT++;
			assert(DfsTo(e.end[1],e.end[0]));
			assert(DfsFrom(e.end[0]));
		}
		for(const int ei:twowayroad)
		{
			const Edge &e=EDGE[ei];
			if(e.d==0)printf("%d %d %d\n",e.end[1]+1,e.end[0]+1,1);
			else printf("%d %d %d\n",e.end[0]+1,e.end[1]+1,e.d==-1?2:1);
		}
	}
	return 0;
}
