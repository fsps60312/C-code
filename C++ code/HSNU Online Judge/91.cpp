#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
const int INF=2147483647;
typedef long long LL;
struct Dot
{
	int x,y;
	Dot(){}
	Dot(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Dot &a)const{return x!=a.x?x<a.x:y<a.y;}
}START,END;
struct Hive
{
	int x1,x2,y1,y2;
	Hive(){}
	Hive(const int _x1,const int _x2,const int _y1,const int _y2):x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
}HIVE[1000];
int N;
bool CmpX1(const Hive &a,const Hive &b){return a.x1<b.x1;}
bool CmpX2(const Hive &a,const Hive &b){return a.x2>b.x2;}
bool CmpY1(const Hive &a,const Hive &b){return a.y1<b.y1;}
bool CmpY2(const Hive &a,const Hive &b){return a.y2>b.y2;}
struct Edge
{
	int u;
	LL c;
	Edge(){}
	Edge(const int _u,const LL _c):u(_u),c(_c){}
};
map<int,int>XIDX,YIDX;
int XMX,YMX;
map<Dot,int>DIDX;
vector<vector<Edge> >ET;
int DotIdx(const Dot &a)
{
	auto it=DIDX.find(a);
	if(it==DIDX.end())
	{
		int sz=DIDX.size();
		ET.push_back(vector<Edge>());
		return DIDX[a]=sz;
	}
	return it->second;
}
void AddEdge(const Dot &a,const Dot &b)
{
	static int i1,i2;
	static LL c;
	i1=DotIdx(a),i2=DotIdx(b);
	c+=abs(a.x-b.x),c+=abs(a.y-b.y);
	ET[i1].push_back(Edge(i2,c));
	ET[i2].push_back(Edge(i1,c));
}
int BUFFER[2003];
void AddHoriEdge(const int x,const int y,const bool toright)
{
	int tmp=(toright?max(BUFFER[y-1],BUFFER[y]):min(BUFFER[y-1],BUFFER[y]));
	if(tmp!=-INF&&tmp!=INF)AddEdge(Dot(tmp,y),Dot(x,y));
}
void BuildRightEdge()
{
	sort(HIVE,HIVE+N,CmpX2);
	for(int i=0;i<=YMX;i++)BUFFER[i]=-INF;
	for(int i=0;i<N;i++)
	{
		Hive &h=HIVE[i];
		AddHoriEdge(h.x1,h.y1,true);
		AddHoriEdge(h.x1,h.y2,true);
		for(int j=h.y1;j<h.y2;j++)BUFFER[j]=h.x2;
	}
}
void BuildLeftEdge()
{
	sort(HIVE,HIVE+N,CmpX1);
	for(int i=0;i<=YMX;i++)BUFFER[i]=INF;
	for(int i=0;i<N;i++)
	{
		Hive &h=HIVE[i];
		AddHoriEdge(h.x2,h.y1,false);
		AddHoriEdge(h.x2,h.y2,false);
		for(int j=h.y1;j<h.y2;j++)BUFFER[j]=h.x1;
	}
}
void AddVertEdge(const int x,const int y,const bool todown)
{
	int tmp=(todown?max(BUFFER[x-1],BUFFER[x]):min(BUFFER[x-1],BUFFER[x]));
	if(tmp!=-INF&&tmp!=INF)AddEdge(Dot(x,tmp),Dot(x,y));
}
void BuildDownEdge()
{
	sort(HIVE,HIVE+N,CmpY2);
	for(int i=0;i<=XMX;i++)BUFFER[i]=-INF;
	for(int i=0;i<N;i++)
	{
		Hive &h=HIVE[i];
		AddVertEdge(h.x1,h.y1,true);
		AddVertEdge(h.x2,h.y1,true);
		for(int j=h.x1;j<h.x2;j++)BUFFER[j]=h.y2;
	}
}
void BuildUpEdge()
{
	sort(HIVE,HIVE+N,CmpY1);
	for(int i=0;i<=XMX;i++)BUFFER[i]=INF;
	for(int i=0;i<N;i++)
	{
		Hive &h=HIVE[i];
		AddVertEdge(h.x1,h.y2,false);
		AddVertEdge(h.x2,h.y2,false);
		for(int j=h.x1;j<h.x2;j++)BUFFER[j]=h.y1;
	}
}
void BuildInsideEdge()
{
	
}
int main()
{
	static int testkase;scanf("%d",&testkase);
	while(testkase--)
	{
		XIDX.clear(),YIDX.clear(),DIDX.clear(),ET.clear();
		scanf("%d%d%d%d",&START.x,&START.y,&END.x,&END.y);
		XIDX[START.x]=XIDX[END.x]=YIDX[START.y]=YIDX[END.y]=-1;
		scanf("%d",&N);
		for(int i=0,x1,x2,y1,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x1>x2)swap(x1,x2);
			if(y1>y2)swap(y1,y2);
			HIVE[i]=Hive(x1,x2,y1,y2);
			XIDX[x1]=XIDX[x2]=YIDX[y1]=YIDX[y2]=-1;
		}
		XMX=1;
		for(auto it=XIDX.begin();it!=XIDX.end();it++)it->second=XMX++;
		YMX=1;
		for(auto it=YIDX.begin();it!=YIDX.end();it++)it->second=YMX++;
		BuildRightEdge(),BuildLeftEdge(),BuildDownEdge(),BuildUpEdge();
		BuildInsideEdge();
	}
	return 0;
}
