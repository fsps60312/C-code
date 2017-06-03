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
//	if(COLOR[u].find(color)!=COLOR[u].end())printf("u=%d,color=%d,ei=%d(%d,%d)\n",u,color,ei,EDGE[ei].a,EDGE[ei].b);
	assert(COLOR[u].find(color)==COLOR[u].end());
	auto it=REMAIN[u].find(color);
	assert(it!=REMAIN[u].end());
	COLOR[u][color]=ei;
	REMAIN[u].erase(it);
	assert((int)(COLOR[u].size()+REMAIN[u].size())==K);
}
int FindColor(const int a,const int ei,const int except)
{
	const int b=(a==EDGE[ei].a?EDGE[ei].b:EDGE[ei].a);
	for(const int c:REMAIN[a])if(c!=except&&REMAIN[b].find(c)!=REMAIN[b].end())return c;
	for(const int c:REMAIN[a])if(c!=except)return c;
	assert(0);return -1;
}
void ColorEdge(const int u,const int ei,const int color)
{
	const Edge &e=EDGE[ei];
	const int pre_color=e.color;
	if(pre_color==color)return;
	EDGE[ei].color=color;
	Uncolor(u,pre_color);
	Color(u,color,ei);
	const int nxt=(u==e.a?e.b:e.a);
//	printf("(%d,%d)\n",u,nxt);
	if(true)
	{
		Uncolor(nxt,pre_color);
		auto it=COLOR[nxt].find(color);
		if(it!=COLOR[nxt].end())
		{
			const int nxtei=it->second;
//			assert(EDGE[nxtei].color==color&&*REMAIN[nxt].begin()!=color);
			ColorEdge(nxt,nxtei,pre_color!=-1?pre_color:FindColor(nxt,nxtei,color));
//			if(COLOR[nxt].find(color)!=COLOR[nxt].end())printf("nxt=%d,nxtei=%d(%d,%d),now=%d(%d,%d)\n",nxt,nxtei,EDGE[nxtei].a,EDGE[nxtei].b,COLOR[nxt][color],EDGE[COLOR[nxt][color]].a,EDGE[COLOR[nxt][color]].b);
		}
		Color(nxt,color,ei);
	}
}
void ColorVertex(const int u)
{
	for(const int ei:ET[u])if(EDGE[ei].color==-1)ColorEdge(u,ei,FindColor(u,ei,-1));
}
int main()
{
//	freopen("in.txt","r",stdin);
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
