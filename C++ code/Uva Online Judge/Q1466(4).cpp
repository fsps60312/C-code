#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
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
vector<int>ADJ[3000],SAT[6000];
Point P[3000][2];
void AddSat(int i1,int i2,int len)
{
	Point &a0=P[i1][0],&a1=P[i1][1],&b0=P[i2][0],&b1=P[i2][1];
	static bool tob0,tob1;
	tob0=(Abs(a0,b0)==len),tob1=(Abs(a0,b1)==len);
	if(tob0&&!tob1)SAT[i1*2].push_back(i2*2);
	else if(tob1&&!tob0)SAT[i1*2].push_back(i2*2+1);
	else if(!tob0&&!tob1)SAT[i1*2].push_back(i2*2),SAT[i1*2].push_back(i2*2+1);
	tob0=(Abs(a1,b0)==len),tob1=(Abs(a1,b1)==len);
	if(tob0&&!tob1)SAT[i1*2+1].push_back(i2*2);
	else if(tob1&&!tob0)SAT[i1*2+1].push_back(i2*2+1);
	else if(!tob0&&!tob1)SAT[i1*2+1].push_back(i2*2),SAT[i1*2+1].push_back(i2*2+1);
}
struct Building
{
	int idx;
	Point loc;
	Building(){}
	Building(int idx,int x,int y):idx(idx),loc(Point(x,y)){}
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
int VIS[6000];
bool BuildP(int u,int iszero)
{
	if(VIS[u]!=-1)return VIS[u]==iszero;
	VIS[u]=iszero;
	Building &b=B[u];
	if(iszero^((b.loc.x+b.loc.y)&1))P[u][0]=b.Crossing(0,0),P[u][1]=b.Crossing(1,1);
	else P[u][0]=b.Crossing(1,0),P[u][1]=b.Crossing(0,1);
	for(int i=0;i<ADJ[u].size();i++)
	{
		Edge &e=EDGE[ADJ[u][i]];
		int &len=e.v;
		if(!BuildP(e.To(u),iszero^(len&1)))return false;
	}
	return true;
}
void BuildSat()
{
	for(int i=0;i<N*2;i++)SAT[i].clear();
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		AddSat(e.a,e.b,e.v);
		AddSat(e.b,e.a,e.v);
	}
}
stack<int>STK;
bool Dfs(int u)
{
	if(VIS[u^1])return false;
	if(VIS[u])return true;
	VIS[u]=true;
	STK.push(u);
	for(int i=0;i<SAT[u].size();i++)
	{
		int &j=SAT[u][i];
		if(!Dfs(j))return false;
	}
	return true;
}
bool SolveSat()
{
	for(int i=0;i<N*2;i+=2)VIS[i]=false;
	for(int i=0;i<N*2;i+=2)
	{
		if(VIS[i]||VIS[i^1])continue;
		STK=stack<int>();
		if(!Dfs(i))
		{
			while(!STK.empty())VIS[STK.top()]=false,STK.pop();
			if(!Dfs(i^1))return false;
		}
	}
	return true;
}
bool SolveZero()
{
	BuildSat();
	return SolveSat();
}
bool SolveOne()
{
	for(int i=0;i<N;i++)VIS[i]=-1;
	BuildP(0,1);
	BuildSat();
	return SolveSat();
}
bool solve()
{
	for(int i=0;i<N;i++)VIS[i]=-1;
	if(!BuildP(0,0))return false;
	if(SolveZero())return true;
	if(SolveOne())return true;
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			for(int i=0;i<N;i++)
			{
				ADJ[i].clear();
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
