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
void Dfs(const int &u,int c,const int &ie)
{
	if(c<DIST[u])
	{
		ANS.push_back(ie);
		static int tol;tol=DIST[u]-c;
		EDGE[ie].toll=tol;
		EDGE[ie].c+=tol;
		c+=tol;
	}
	if(INQ[u]==KASE)return;
	INQ[u]=KASE;
	for(int i=0;i<AD[u].size();i++)
	{
		Edge &e=EDGE[AD[u][i]];
		Dfs(e.b,c+e.c,AD[u][i]);
	}
}
bool Check()
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
			if(DIST[u]+(e.toll?1:0)<=DIST[e.b])continue;
			DIST[e.b]=DIST[u]+(e.toll?1:0);
			if(INQ[e.b]!=KASE)
			{
				q.push(e.b);
				INQ[e.b]=KASE;
			}
		}
	}
	return DIST[N-1]<=1;
}
int main()
{
	for(int i=0;i<50000;i++)INQ[i]=0;
	while(scanf("%d%d",&N,&R)==2&&N&&R)
	{
		EDGE.clear(),ANS.clear();
		for(int i=0;i<N;i++)AD[i].clear();
		for(int i=0;i<R;i++)
		{
			static int a,b,c,sz;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			sz=EDGE.size();
			EDGE.push_back(Edge(a,b,c));
			AD[a].push_back(sz);
		}
		Bfs();
		KASE++;
		Dfs(0,0,-1);
		static int kase=1;
		printf("Case %d: ",kase++);
		int ans=DIST[N-1];
		if(!Check())printf("No solution\n");
		else
		{
			printf("%d %d\n",ANS.size(),ans);
			sort(ANS.begin(),ANS.end());
			for(int i=0;i<ANS.size();i++)printf("%d %d\n",ANS[i]+1,EDGE[ANS[i]].toll);
		}
	}
	return 0;
}
