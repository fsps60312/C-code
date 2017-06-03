#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Edge
{
	int A,B,COST;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST){}
};
bool operator<(const Edge &a,const Edge &b){return a.COST<b.COST;}
int N,M;
vector<Edge>EDGE;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		DJ.Clear(N);
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			EDGE.push_back(Edge(a,b,c));
		}
		sort(EDGE.begin(),EDGE.end());
		for(int i=M-1;i>=0;i--)
		{
			const Edge &e=EDGE[i];
			if(DJ.Merge(e.A,e.B))
			{
				EDGE[i].VIS=true;
			}
		}
		DJ.Clear(N);
		for(int i=0;i<M;i++)
		{
			
		}
	}
	return 0;
}
