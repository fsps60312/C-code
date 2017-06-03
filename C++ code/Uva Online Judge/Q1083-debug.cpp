#include<bits/stdc++.h>
using namespace std;
void getmax(int &a,int b){if(b>a)a=b;}
struct Edge
{
	int b,cost,type;
	Edge(){}
	Edge(int b,int c,int t):b(b),cost(c),type(t){}
};
vector<Edge>EDGE;
int DIST[50000],ANS[50000],OUT[50000],IN[50000],TOLL[50000],N,M;
vector<int>AD[500000];
bool BI[50000],VIS[50000];
void AddEdge(int a,int b,int c,int type)
{
	int sz=EDGE.size();
	EDGE.push_back(Edge(b,c,type));
	AD[a].push_back(sz);
}
void Solve()
{
	queue<int>q;
	q.push(0);
	for(int i=0;i<N;i++)DIST[i]=0,BI[i]=false;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(e.type==0)continue;
			getmax(DIST[e.b],DIST[u]+e.cost);
			if(!--IN[e.b])q.push(e.b);
		}
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(e.type==1)continue;
			if(BI[e.b]==true){BI[u]=true;break;}
			if(DIST[e.b]+e.cost!=DIST[u]){BI[u]=true;break;}
		}
	}
}
bool Check()
{
	queue<int>q;
	for(int i=0;i<N;i++)TOLL[i]=0,VIS[i]=false;
	q.push(N-1);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		VIS[u]=true;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(e.type==1)continue;
			if(!--OUT[e.b])q.push(e.b);
			int s=DIST[u]-(DIST[e.b]+e.cost)+TOLL[u];
			if(!BI[e.b])ANS[AD[u][i]/2]+=s;//first need to add toll
			else
			{
				if(VIS[e.b]&&TOLL[e.b]!=s)return false;//why???
				TOLL[e.b]=s;//why???
			}
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)&&N+M!=0)
	{
		for(int i=0;i<N;i++)
		{
			IN[i]=OUT[i]=0;
			AD[i].clear();
		}
		for(int i=0;i<M;i++)
		{
			ANS[i]=0;
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			IN[b]++,OUT[a]++;
			AddEdge(a,b,c,1),AddEdge(b,a,c,0);
		}
		Solve();
		static int kase=0;kase++;
		if(!Check())printf("Case %d: No solution\n",kase);
		else
		{
			int ans=0;
			for(int i=0;i<M;i++)if(ANS[i]!=0)ans++;
			printf("Case %d: %d %d\n",kase,ans,DIST[N-1]);
			for(int i=0;i<M;i++)if(ANS[i]!=0)printf("%d %d\n",i+1,ANS[i]);
		}
	}
	return 0;
}
