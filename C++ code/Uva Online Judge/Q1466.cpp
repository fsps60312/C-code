#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,N,M;
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
};
int Abs(Point a,Point b){return abs(a.x-b.x)+abs(a.y-b.y);}
vector<int>ADJ[3000],SAT[24000];
inline void AddSat(int i1,bool b1,int i2,bool b2)
{
	i1<<=1,i2<<=1;
	if(b1)i1++;if(b2)i2++;
	SAT[i1].push_back(i2);
}
struct Building
{
	int idx;
	Point loc;
	bool valid[2][2];
	Building(){}
	Building(int idx,int _x,int _y):idx(idx),loc(Point(_x,_y))
	{
		static int x,y,a,b;
		for(x=0;x<2;x++)for(y=0;y<2;y++)valid[x][y]=true;
		for(x=0;x<2;x++)for(y=0;y<2;y++)for(a=0;a<2;a++)for(b=0;b<2;b++)
		{
			if(a==x&&b==y)continue;
			AddSat(Idx(x,y),true,Idx(a,b),false);
		}
	}
	int Idx(int dx,int dy){return idx*4+dx*2+dy;}
	Point Crossing(int dx,int dy){return Point(loc.x+dx,loc.y+dy);}
};
vector<Building>B;
struct Edge
{
	int a,b,v;
	Edge(){}
	Edge(int a,int b,int v):a(a),b(b),v(v){}
	int To(int from){return from!=a?a:b;}
};
vector<Edge>EDGE;
inline void UpdateValid(Building &b1,Building &b2,int len)
{
	static int dis,x1,y1,x2,y2;
	static int v1[2][2],v2[2][2];
	for(x1=0;x1<2;x1++)for(y1=0;y1<2;y1++)v1[x1][y1]=v2[x1][y1]=false;
	for(x1=0;x1<2;x1++)for(y1=0;y1<2;y1++)
	{
		if(!b1.valid[x1][y1])continue;
		static int cnt,x,y;
		cnt=0;
		for(x2=0;x2<2;x2++)for(y2=0;y2<2;y2++)
		{
			if(!b2.valid[x2][y2])continue;
			if(Abs(b1.Crossing(x1,y1),b2.Crossing(x2,y2))==len)cnt++,x=x2,y=y2;
			else AddSat(b1.Idx(x1,y1),true,b2.Idx(x2,y2),false);
		}
		if(cnt==1)AddSat(b1.Idx(x1,y1),true,b2.Idx(x,y),true);
	}
	for(x1=0;x1<2;x1++)for(y1=0;y1<2;y1++)
	{
		b1.valid[x1][y1]&=v1[x1][y1];
		b2.valid[x1][y1]&=v2[x1][y1];
	}
}
bool solve()
{
	for(int i=0;i<M;i++)UpdateValid(B[EDGE[i].a],B[EDGE[i].b],EDGE[i].v);
	
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			for(int i=0;i<N;i++)
			{
				ADJ[i].clear();
				for(int j=0;j<8;j++)SAT[i*8+j].clear();
			}
			B.clear(),EDGE.clear();
			for(int x,y,i=0;i<N;i++)
			{
				scanf("%d%d",&x,&y);
				B.push_back(Building(i,x,y));
			}
			scanf("%d",&M);
			for(int a,b,v,sz,i=0;i<M;i++)
			{
				scanf("%d%d%d",&a,&b,&v);
				a--,b--;
				sz=EDGE.size();
				ADJ[a].push_back(sz);
				ADJ[b].push_back(sz);
				EDGE.push_back(Edge(a,b,v));
			}
			printf("%spossible\n",solve()?"":"im");
		}
	}
	return 0;
}
