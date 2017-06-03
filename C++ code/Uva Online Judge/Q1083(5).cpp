#include<bits/stdc++.h>
using namespace std;
int N,R,DIST[50000],INQ[50000],KASE=0;
struct Edge
{
	int toll,a,b,c;
	Edge(){}
	Edge(const int &a,const int &b,const int &c):toll(0),a(a),b(b),c(c){}
};
vector<Edge>EDGE;
vector<int>AD[50000];
vector<int>ANS;
void Bfs()
{
	for(int i=0;i<N;i++)DIST[i]=-1;
	queue<int>q;
	KASE++;
	DIST[0]=0;
	q.push(0);
	INQ[0]=KASE;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		INQ[u]=0;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(DIST[u]+e.c<=DIST[e.b])continue;
			DIST[e.b]=DIST[u]+e.c;
			if(INQ[e.b]!=KASE)
			{
				q.push(e.b);
				INQ[e.b]=KASE;
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<50000;i++)INQ[i]=0;
	while(scanf("%d%d",&N,&R)==2&&N&&R)
	{
		assert(N>=2&&N<=50000);
		EDGE.clear(),ANS.clear();
		for(int i=0;i<N;i++)AD[i].clear();
		for(int i=0;i<R;i++)
		{
			static int a,b,c,sz;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			assert(a>=0&&b>=0&&a<N&&b<N);
			sz=EDGE.size();
			EDGE.push_back(Edge(a,b,c));
			AD[a].push_back(sz);
		}
		Bfs();
		int ans=DIST[N-1];
		assert(ans>0);
		for(int i=0;i<R;i++)
		{
			Edge &e=EDGE[i];
			assert(DIST[e.a]+e.c<=DIST[e.b]);
			if(DIST[e.a]+e.c<DIST[e.b])
			{
				ANS.push_back(i);
				e.toll=DIST[e.b]-(DIST[e.a]+e.c);
				e.c=1;
			}
			else e.c=0;
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		Bfs();
		if(DIST[N-1]>1)puts("No solution");
		else
		{
			printf("%d %d\n",ANS.size(),ans);
			for(int i=0;i<ANS.size();i++)printf("%d %d\n",ANS[i]+1,EDGE[ANS[i]].toll);
		}
	}
	return 0;
}
/*
5 11
1 3 8
1 2 5
1 3 6
1 4 2
2 4 1
2 5 1
2 4 9
2 4 5
2 5 8
3 4 3
4 5 6
*/
