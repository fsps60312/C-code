#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<cassert>
#include<queue> 
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N;
struct Edge
{
	int u;
	LL c;
	Edge(){}
	Edge(const int _u,const LL _c):u(_u),c(_c){}
};
vector<vector<Edge> >ET;
struct Dot
{
	LL x,y;
	Dot(){}
	Dot(const LL _x,const LL _y):x(_x),y(_y){}
	bool operator<(const Dot &a)const{return x!=a.x?x<a.x:y<a.y;}
}START,END;
vector<Dot>DOT;
map<Dot,int>DID;
LL Dist(const Dot &a,const Dot &b){return abs(a.x-b.x)+abs(a.y-b.y);}
struct Hive
{
	LL rim[4];
	vector<LL>dot[4];
	Hive(){}
	Hive(const LL x1,const LL x2,const LL y1,const LL y2):rim{y1,x2,y2,x1}{}
}HIVE[1002];
bool CmpUp(const int &a,const int &b){return HIVE[a].rim[0]>HIVE[b].rim[0];}
bool CmpRight(const int &a,const int &b){return HIVE[a].rim[1]<HIVE[b].rim[1];}
bool CmpDown(const int &a,const int &b){return HIVE[a].rim[2]<HIVE[b].rim[2];}
bool CmpLeft(const int &a,const int &b){return HIVE[a].rim[3]>HIVE[b].rim[3];}
map<LL,int>IDX[2];
map<int,LL>RID[2];
int MX[2];
int DotIdx(const Dot &d)
{
	auto it=DID.find(d);
	if(it==DID.end())
	{
		int sz=DID.size();
		ET.push_back(vector<Edge>());
		DOT.push_back(d);
		return DID[d]=sz;
	}
	else return it->second;
}
void AddEdge(const Dot &a,const Dot &b)
{
	static int ia,ib;
	ia=DotIdx(a),ib=DotIdx(b);
	ET[ia].push_back(Edge(ib,Dist(a,b)));
	ET[ib].push_back(Edge(ia,Dist(a,b)));
}
int BUFFER[2003],TICK[2003];
void AddDotEdge(const int d,const int loc,const int anot)
{
	if(TICK[loc-1]==-1&&TICK[loc]==-1)return;
	int idx=(TICK[loc-1]>TICK[loc]?BUFFER[loc-1]:BUFFER[loc]);
	Hive &h=HIVE[idx];
	if(d&1)AddEdge(Dot(h.rim[d],RID[d&1][loc]),Dot(anot,RID[d&1][loc]));
	else AddEdge(Dot(RID[d&1][loc],h.rim[d]),Dot(RID[d&1][loc],anot));
	h.dot[d].push_back(RID[d&1][loc]);
}
void ConnectHives(int direction)
{
	static int order[1002];
	for(int i=0;i<N;i++)order[i]=i;
	switch(direction)
	{
		case 0:sort(order,order+N,CmpUp);break;
		case 1:sort(order,order+N,CmpRight);break;
		case 2:sort(order,order+N,CmpDown);break;
		case 3:sort(order,order+N,CmpLeft);break;
		default:assert(0);
	}
	const int d=direction;
	for(int i=0;i<=MX[d&1];i++)TICK[i]=-1;
	for(int _i=0;_i<N;_i++)
	{
		const Hive &h=HIVE[order[_i]];
		AddDotEdge(d,IDX[d&1][h.rim[d^1]],h.rim[d^2]);
		AddDotEdge(d,IDX[d&1][h.rim[d^2^1]],h.rim[d^2]);
		for(int i=IDX[d&1][h.rim[(d&1)?0:3]];i<IDX[d&1][h.rim[(d&1)?2:1]];i++)TICK[i]=_i,BUFFER[i]=order[_i];
	}
}
void ConnectDots(int direction)
{
	const int d=direction;
	for(int i=0;i<N;i++)
	{
		Hive &h=HIVE[i];
		int l=min(h.rim[d^1],h.rim[d^2^1]),r=max(h.rim[d^1],h.rim[d^2^1]);
		vector<LL>&v=h.dot[d];
		v.push_back(l),v.push_back(r);
		sort(v.begin(),v.end());
		v.resize(unique(v.begin(),v.end())-v.begin());
		for(int j=1;j<v.size();j++)
		{
			if(d&1)AddEdge(Dot(h.rim[d],v[j-1]),Dot(h.rim[d],v[j]));
			else AddEdge(Dot(v[j-1],h.rim[d]),Dot(v[j],h.rim[d]));
		}
	}
}
vector<LL>DIST;
vector<bool>INQ;
void Bfs()
{
	DIST.resize(DID.size()),INQ.resize(DID.size());
	for(int i=0;i<DIST.size();i++)DIST[i]=INF,INQ[i]=false;
	queue<int>q;
	q.push(0),INQ[0]=true;
	DIST[0]=0LL;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(DIST[u]+e.c<DIST[e.u])
			{
				DIST[e.u]=DIST[u]+e.c;
				if(!INQ[e.u])
				{
					q.push(e.u);
					INQ[e.u]=true;
				}
			}
		}
	}
}
bool Conflict(const Hive &h,const Dot &d){return h.rim[0]<=d.y&&d.y<=h.rim[2]&&h.rim[3]<=d.x&&d.x<=h.rim[1];}
int main()
{
//	freopen("in.txt","r",stdin);
	static int testkase;scanf("%d",&testkase);
	while(testkase--)
	{
		DOT.clear(),DID.clear();
		for(int i=0;i<2;i++)IDX[i].clear(),RID[i].clear();
		ET.clear();
		scanf("%lld%lld%lld%lld",&START.x,&START.y,&END.x,&END.y);
		scanf("%d",&N);
		DotIdx(START),DotIdx(END);
		IDX[0][START.x]=IDX[0][END.x]=IDX[1][START.y]=IDX[1][END.y]=-1;
		for(int i=0;i<N;i++)
		{
			static LL x1,y1,x2,y2;
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			if(x1>x2)swap(x1,x2);
			if(y1>y2)swap(y1,y2);
			HIVE[i]=Hive(x1,x2,y1,y2);
			IDX[0][x1]=IDX[0][x2]=IDX[1][y1]=IDX[1][y2]=-1;
			assert(!Conflict(HIVE[i],START)&&!Conflict(HIVE[i],END));
		}
		HIVE[N++]=Hive(START.x,START.x,START.y,START.y);
		HIVE[N++]=Hive(END.x,END.x,END.y,END.y);
		MX[0]=MX[1]=1;
		for(int i=0;i<2;i++)for(auto it=IDX[i].begin();it!=IDX[i].end();it++)it->second=MX[i]++,RID[i][it->second]=it->first;
		for(int d=0;d<4;d++)ConnectHives(d);
		for(int d=0;d<4;d++)ConnectDots(d);
		Bfs();
		if(DIST[1]==INF)puts("No Path");
		else printf("%d\n",DIST[1]);
	}
	return 0;
}
