#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int a,b,color;
	Edge(){}
	Edge(const int _a,const int _b,const int _color):a(_a),b(_b),color(_color){}
};
vector<Edge>EDGE;
int A,N,M,K;
vector<int>ET[2000];
map<int,int>COLOR[2000];
set<int>REMAIN[2000];
void Uncolor(const int u,const int color)
{
	if(color==-1)return;
	auto it=COLOR[u].find(color);
	assert(it!=COLOR[u].end());
	COLOR[u].erase(it);
	REMAIN[u].insert(color);
	assert((int)(COLOR[u].size()+REMAIN[u].size())==K);
}
void Color(const int u,const int color,const int ei)
{
	if(COLOR[u].find(color)!=COLOR[u].end())printf("u=%d,color=%d,ei=%d(%d,%d)\n",u,color,ei,EDGE[ei].a,EDGE[ei].b);
	assert(COLOR[u].find(color)==COLOR[u].end());
	auto it=REMAIN[u].find(color);
	assert(it!=REMAIN[u].end());
	COLOR[u][color]=ei;
	REMAIN[u].erase(it);
	assert((int)(COLOR[u].size()+REMAIN[u].size())==K);
}
void ColorEdge(const int u,const int ei,const int color)
{
	const Edge &e=EDGE[ei];
	if(e.color==color)return;
	printf("color(%d,%d):%d->%d\n",e.a,e.b,e.color,color);
	Uncolor(u,e.color);
	puts("a");
	Color(u,color,ei);
	puts("b");
	const int nxt=(u==e.a?e.b:e.a);
	if(true)
	{
		Uncolor(nxt,e.color);
		puts("c");
		auto it=COLOR[nxt].find(color);
		if(it!=COLOR[nxt].end())
		{
			const int nxtei=it->second;
			assert(EDGE[nxtei].color==color);
			ColorEdge(nxt,nxtei,*REMAIN[nxt].begin());
			assert(EDGE[nxtei].color!=color&&COLOR[nxt][EDGE[nxtei].color]==nxtei);
			if(COLOR[nxt].find(color)!=COLOR[nxt].end())printf("nxt=%d,nxtei=%d(%d,%d),now=%d(%d,%d)\n",nxt,nxtei,EDGE[nxtei].a,EDGE[nxtei].b,COLOR[nxt][color],EDGE[COLOR[nxt][color]].a,EDGE[COLOR[nxt][color]].b);
		}
		Color(nxt,color,ei);
	}
	printf("done color(%d,%d):%d->%d\n",e.a,e.b,e.color,color);
	EDGE[ei].color=color;
}
void ColorVertex(const int u)
{
	for(const int ei:ET[u])if(EDGE[ei].color==-1)ColorEdge(u,ei,*REMAIN[u].begin());
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&A,&N,&M),N+=A;
	for(int i=0;i<N;i++)ET[i].clear(),COLOR[i].clear(),REMAIN[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--,b+=A;
		EDGE.push_back(Edge(a,b,-1));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	K=0;
	for(int i=0;i<N;i++)getmax(K,(int)ET[i].size());
	for(int i=0;i<N;i++)for(int c=0;c<K;c++)REMAIN[i].insert(c);
	for(int i=0;i<N;i++)ColorVertex(i);
	printf("%d\n",K);
	assert(M==(int)EDGE.size());
	for(int i=0;i<M;i++)
	{
		if(i)putchar(' ');
		printf("%d",EDGE[i].color+1);
	}
	puts("");
	return 0;
}
