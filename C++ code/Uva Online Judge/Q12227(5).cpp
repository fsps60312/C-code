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
};
int Hypot(int a,int b,int c){double v=sqrt(a*a+b*b+c*c);if(abs(v-(int)v)<EPS)return (int)v;return (int)(v+1.0);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
#include<stack>
stack<int>DP[50];
bool VIS[50],INQ[50];
int DT[50];
int Dfs(int u,int dt)
{
	if(VIS[u])
	{
		if(dt>=DT[u])return -1;
		return u;
	}
	INQ[u]=false;
	VIS[u]=true;
	DT[u]=dt;
	for(int i=0;i<N;i++)
	{
		Warmhole &wu=WARMHOLE[u];
		Warmhole &w=WARMHOLE[i];
		int res=Dfs(i,dt+min(Dis(wu.exit,w.exit),Dis(wu.exit,w.entry)+w.shift));
		if(res!=-1)
		{
			INQ[u]=true;
			return res==u?-1:res;
		}
	}
	return -1;
}
int Solve()
{
	for(int i=0;i<N;i++)
	{
		DP[i]=stack<int>();
		DP[i].push(INF);
	}
	queue<Pq>q;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)VIS[j]=false;
		if(Dfs(i,0)==-1)continue;
		int k=-1;
		for(int j=0;j<N;j++)if(INQ[j])
		{
			if(k==-1||(DT[j]-WARMHOLE[j].creation<DT[k]-WARMHOLE[k].creation))k=j;
		}
		assert(k!=-1);
		Warmhole &w=WARMHOLE[k];
		q.push(Pq(k,w.exit,w.creation+w.shift));
//		printf("push(%d,%d)\n",k,w.creation+w.shift);
	}
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		q.push(Pq(i,w.exit,min(Dis(BEGIN,w.exit),Dis(BEGIN,w.entry)+w.shift)));
	}
	while(!q.empty())
	{
		Pq p=q.front();q.pop();
		if(DP[p.u].top()<=p.t)continue;
		DP[p.u].push(p.t);
//		printf("u=%d,(%d,%d,%d),t=%d\n",p.u,p.loc.x,p.loc.y,p.loc.z,p.t);
		for(int i=0;i<N;i++)
		{
			Warmhole &w=WARMHOLE[i];
			if(p.t+Dis(p.loc,w.entry)<w.creation)continue;
			q.push(Pq(i,w.exit,p.t+min(Dis(p.loc,w.exit),Dis(p.loc,w.entry)+w.shift)));
		}
	}
	int ans=Dis(BEGIN,END);
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		ans=min(ans,DP[i].top()+Dis(w.exit,END));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
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
