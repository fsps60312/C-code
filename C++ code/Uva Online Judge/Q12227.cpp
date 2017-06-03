#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<cassert>
using namespace std;
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
	Point loc,t;
	Pq(){}
	Pq(Point loc,int t):loc(loc),t(t){}
	Pq(int x,int y,int z,int t):loc(Point(x,y,z)),t(t){}
	bool operator<(const Pq &p)const{return t>p.t;}
};
int Hypot(int a,int b,int c){return (int)(sqrt(a*a+b*b+c*c)+0.5);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
int Solve()
{
	priority_queue<Pq>pq;
	pq.push(Pq(BEGIN,0));
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(Dis(w.entry,w.exit)+w.shift<0)pq.push(Pq(w.exit,w.creation+w.shift));
	}
	int ans=Dis(BEGIN,END);
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		getmin(ans,p.t+Dis(p.loc,END));
		for(int i=0;i<N;i++)
		{
			Warmhole &w=WARMHOLE[i];
			int t=p.t+Dis(p.loc,w.entry);
			if(t<w.creation)continue;
			pq.push(Pq(w.exit,t));
		}
	}
	assert(0);
}
int main()
{
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
		}
		printf("%d\n",Solve());
	}
	return 0;
}
