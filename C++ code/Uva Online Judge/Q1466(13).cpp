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
};
inline int Abs(Point &a,Point &b){return abs(a.x-b.x)+abs(a.y-b.y);}
vector<int>ADJ[3000],SAT[6000];
Point P[3000][2];
inline void AddSat(int &i1,int &i2,int &len)
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
int VS[6000],VG[3000];
int STK_VG[3000],STK_VG_CNT;
bool BuildP(int u,int iszero,vector<int>&s)
{
	if(VG[u]!=-1)return VG[u]==iszero;
	VG[u]=iszero;
	STK_VG[STK_VG_CNT++]=u;
	Building &b=B[u];
	if(iszero^((b.loc.x+b.loc.y)&1))P[u][0]=b.Crossing(0,0),P[u][1]=b.Crossing(1,1);
	else P[u][0]=b.Crossing(1,0),P[u][1]=b.Crossing(0,1);
	s.push_back(u);
	for(int i=0;i<ADJ[u].size();i++)
	{
		Edge &e=EDGE[ADJ[u][i]];
		int &len=e.v;
		if(!BuildP(e.To(u),iszero^(len&1),s))return false;
	}
	return true;
}
bool VE[300000];
void BuildSat(vector<int>&s)
{
	for(int i=0;i<s.size();i++)SAT[s[i]*2].clear(),SAT[s[i]*2+1].clear();
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		if(VE[i]||VG[e.a]==-1)continue;
		AddSat(e.a,e.b,e.v);
		AddSat(e.b,e.a,e.v);
	}
}
int STK[6000],STK_CNT;
bool Dfs(int u)
{
	if(VS[u^1])return false;
	if(VS[u])return true;
	VS[u]=true;
	STK[STK_CNT++]=u;
	for(int i=0;i<SAT[u].size();i++)
	{
		int &j=SAT[u][i];
		if(!Dfs(j))return false;
	}
	return true;
}
bool SolveSat(vector<int>&s)
{
	for(int i=0;i<s.size();i++)VS[s[i]*2]=VS[s[i]*2+1]=false;
	for(int _i=0,i;_i<s.size();_i++)
	{
		i=s[_i]*2;
		if(VS[i]||VS[i^1])continue;
		STK_CNT=0;
		if(!Dfs(i))
		{
			while(STK_CNT)VS[STK[--STK_CNT]]=false;
			if(!Dfs(i^1))return false;
		}
	}
	return true;
}
bool SolveZero(int idx,bool &built)
{
	vector<int>s;
	if(!(built=BuildP(idx,0,s)))return false;
	BuildSat(s);
	return SolveSat(s);
}
bool SolveOne(int idx,bool &built)
{
	if(!built)return false;
	vector<int>s;
	while(STK_VG_CNT)VG[STK_VG[--STK_VG_CNT]]=-1;
	if(!BuildP(idx,1,s))return false;
	BuildSat(s);
	return SolveSat(s);
}
bool solve()
{
	for(int i=0;i<N;i++)VG[i]=-1;
	for(int i=0;i<N;i++)
	{
		if(VG[i]!=-1)continue;
		STK_VG_CNT=0;
		static bool built;
		if(!SolveZero(i,built)&&!SolveOne(i,built))return false;
		STK_VG_CNT=0;
		for(int j=0;j<M;j++)
		{
			Edge &e=EDGE[j];
			if(VG[e.a]==-1)continue;
			VE[j]=true;
		}
	}
	return true;
}
int main()
{
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
				VE[i]=false;
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
