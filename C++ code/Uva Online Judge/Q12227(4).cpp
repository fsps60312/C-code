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
struct Pq
{
	Point loc;
	int u,t;
	Pq(){}
	Pq(int u,Point loc,int t):u(u),loc(loc),t(t){}
	Pq(int x,int y,int z,int t):loc(Point(x,y,z)),t(t){}
	bool operator<(const Pq &p)const{return t>p.t;}
};
int Hypot(int a,int b,int c){double v=sqrt(a*a+b*b+c*c);if(abs(v-(int)v)<EPS)return (int)v;return (int)(v+1.0);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
vector<Point>P;
int DP[52];
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
int AD[50][50];
void CheckNegaCycle(int root)
{
	queue<int>qu,qv;
	static int mn[52],cnt[52];
	for(int i=0;i<N;i++)mn[i]=INF,cnt[i]=0;
	qu.push(root),qv.push_back(0);
	while(!qu.empty())
	{
		int u=qu.front(),v=qv.front();
		qu.pop(),qv.pop();
		if(mn[u]<=v)continue;
		mn[u]=v;
		cnt[u]++;
		if()
		for(int i=0;i<N;i++)
		{
			qu.push(i);
			qv.push(AD[u][i]);
		}
	}
}
int Solve()
{
	P.clear();
	for(int i=0;i<N;i++)P.push_back(WARMHOLE[i].exit);
	P.push_back(BEGIN),P.push_back(END);
	for(int i=0;i<N+2;i++)DP[i]=INF;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			Warmhole &w=WARMHOLE[j];
			AD[i][j]=min(Dis(P[i],P[j]),Dis(P[i],w.entry)+w.t);
		}
	}
	for(int i=0;i<N;i++)CheckNegaCycle(i);
	priority_queue<Pq>pq;
	pq.push(Pq(N,BEGIN,0));
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(DP[i]!=INF)pq.push(Pq(i,w.exit,DP[i]));
	}
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(DP[p.u]<=p.t)continue;
//		printf("u=%d,(%d,%d,%d),t=%d\n",p.u,p.loc.x,p.loc.y,p.loc.z,p.t);
		DP[p.u]=p.t;
		pq.push(Pq(N+1,END,p.t+Dis(p.loc,END)));
		for(int i=0;i<N;i++)
		{
			Warmhole &w=WARMHOLE[i];
			int t=p.t+Dis(p.loc,w.entry);
			if(t<w.creation)t=p.t+Dis(p.loc,w.exit);
			else t=min(t+w.shift,p.t+Dis(p.loc,w.exit));
			pq.push(Pq(i,w.exit,t));
		}
	}
	return DP[N+1];
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
			printf("%d\n",Solve());
		}
	}
	return 0;
}
