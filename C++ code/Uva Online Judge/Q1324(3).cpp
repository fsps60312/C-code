#include<cstdio>
#include<vector>
using namespace std;
int N,M,K,S,T;
struct Point
{
	int x,y;
};
struct Edge
{
	Point to;
	int limit,flow;
	void init(Point t,int l)
	{
		to=t,limit=l;
		flow=0;
	}
	void clear(){limit=-1000,flow=1000;}
};
Edge EDGE[101][51];
int main()
{
	while(scanf("%d%d%d%d%d",&N,&M,&K,&S,&T)==5)
	{
		for(int i=0;i<N+K;i++)
		{
			for(int j=0;j<N;j++)
			{
				EDGE[i][j].clear();
			}
		}
		for(int i=0;i<M;;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			EDGE[0][u].init((Point){1,v},1);
			EDGE[1][v].init((Point){0,u},0);
			EDGE[0][v].init((Point){1,u},1);
			EDGE[1][u].init((Point){0,v},0);
		}
		for(int i=1;i<=N;i++)
		{
			EDGE[0][i].init((Point){1,i},1000);
			EDGE[1][i].init((Point){0,i},0);
		}
	}
	return 0;
}
