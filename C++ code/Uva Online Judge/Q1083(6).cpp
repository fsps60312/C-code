#include<bits/stdc++.h>
using namespace std;
int N,R;
void getmax(int &a,int b){if(b>a)a=b;}
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &a,const int &b,const int &c):a(a),b(b),c(c){}
};
vector<Edge>EDGE;
vector<int>ET[50000],EF[50000];
int IN[50000],OUT[50000];
int DIST[50000];
bool OPT[50000];
void Bfs()
{
	for(int i=0;i<N;i++)DIST[i]=0,OPT[i]=true;
	queue<int>q;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			Edge &e=EDGE[ET[u][i]];
			getmax(DIST[e.b],DIST[e.a]+e.c);
			if(!--IN[e.b])q.push(e.b);
		}
		for(int i=0;i<EF[u].size();i++)
		{
			Edge &e=EDGE[EF[u][i]];
			if(!OPT[e.a]||DIST[e.a]+e.c<DIST[e.b]){OPT[u]=false;break;}
		}
	}
}
int TOLL[50000];
struct Ans
{
	int idx,toll;
	Ans(){}
	Ans(const int &i,const int &t):idx(i),toll(t){}
	bool operator<(const Ans &a)const{return idx<a.idx;}
};
vector<Ans>ANS;
bool Check()
{
	for(int i=0;i<N;i++)TOLL[i]=-1;
	queue<int>q;
	q.push(N-1);
	TOLL[N-1]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(OPT[u])continue;
		for(auto i=EF[u].begin();i!=EF[u].end();i++)
		{
			Edge &e=EDGE[*i];
			int toll=DIST[e.b]-(DIST[e.a]+e.c)+TOLL[e.b];
			if(OPT[e.a])
			{
				if(toll)ANS.push_back(Ans((*i)+1,toll));
				TOLL[e.a]=0;
			}
			else
			{
				if(TOLL[e.a]==-1)TOLL[e.a]=toll;
				else if(TOLL[e.a]!=toll)return false;
			}
			if(!--OUT[e.a])q.push(e.a);
		}
	}
	return true;
}
int main()
{
	while(scanf("%d%d",&N,&R)==2&&N&&R)
	{
		for(int i=0;i<N;i++)
		{
			ET[i].clear(),EF[i].clear();
			OUT[i]=IN[i]=0;
		}
		EDGE.clear(),ANS.clear();
		for(int i=0,a,b,c,sz;i<R;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			OUT[--a]++,IN[--b]++;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			EF[b].push_back(i);
		}
		Bfs();
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!Check())puts("No solution");
		else
		{
			sort(ANS.begin(),ANS.end());
			printf("%d %d\n",ANS.size(),DIST[N-1]);
			for(int i=1;i<ANS.size();i++)assert(ANS[i-1].idx<ANS[i].idx);
			for(auto ans=ANS.begin();ans!=ANS.end();ans++)printf("%d %d\n",(*ans).idx,(*ans).toll);
		}
	}
	return 0;
}
