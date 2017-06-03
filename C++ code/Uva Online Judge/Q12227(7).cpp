#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<cassert>
using namespace std;
const int INF=2147483647;
const double EPS=1e-9;
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z){}
	void Scanf(){scanf("%d%d%d",&x,&y,&z);}
}BEGIN,END;
int T,N;
struct Warmhole
{
	Point entry,exit;
	int creation,shift;
	void Scanf()
	{
		entry.Scanf(),exit.Scanf();
		scanf("%d%d",&creation,&shift);
	}
};
vector<Warmhole>WARMHOLE;
int Hypot(int a,int b,int c){double v=sqrt(a*a+b*b+c*c);if(abs(v-(int)v)<EPS)return (int)v;return (int)(v+1.0);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
struct Edge
{
	int to,creation,shift,cost;
	Edge(int to=0,int creation=0,int shift=0,int cost=0):to(to),creation(creation),shift(shift),cost(cost){}
};
vector<Edge>AD[50];
int TIME[50],UPRE[50],CPRE[50];
bool INQ[50];
int Solve()
{
	queue<int>q;
	for(int i=0;i<N;i++)
	{
		q.push(i);
		Warmhole &w=WARMHOLE[i];
		TIME[i]=min(Dis(BEGIN,w.exit),max(w.creation,Dis(BEGIN,w.entry))+w.shift);
		UPRE[i]=-1;
		INQ[i]=true;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			int time=max(TIME[u]+e.cost,e.creation)+e.shift;
			if(time>=TIME[e.to])continue;
			TIME[e.to]=time;
			UPRE[e.to]=u,CPRE[e.to]=e.creation;
			if(!INQ[e.to])INQ[e.to]=true,q.push(e.to);
		}
	}
	int ans=Dis(BEGIN,END);
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(TIME[i]+Dis(w.exit,END)<ans)ans=TIME[i]+Dis(w.exit,END);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			BEGIN.Scanf(),END.Scanf();
			scanf("%d",&N);
			WARMHOLE.clear();
			for(int i=0;i<N;i++)
			{
				static Warmhole w;
				w.Scanf();
				WARMHOLE.push_back(w);
			}
			for(int i=0;i<N;i++)AD[i].clear();
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)
				{
					Warmhole &w1=WARMHOLE[i],&w2=WARMHOLE[j];
					AD[i].push_back(Edge(j,-INF,0,Dis(w1.exit,w2.exit)));
					AD[i].push_back(Edge(j,w2.creation,w2.shift,Dis(w1.exit,w2.entry)));
				}
			}
			printf("%d\n",Solve());
		}
	}
	return 0;
}
