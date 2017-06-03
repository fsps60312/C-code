#include<cstdio>
#include<map>
#include<queue>
#include<cassert>
using namespace std;
int N,M;
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(_a),b(_b){}
	bool operator<(const Pair &p)const{return a!=p.a?a<p.a:b<p.b;}
};
struct Line
{
	int idx,cnt;
	vector<int>time;
};
vector<Line>LINE;
map<Pair,int>IDX;
struct Edge
{
	int to,cost,start;
	Edge(){}
	Edge(const int _t,const int _c,const int _s):to(_t),cost(_c),start(_s){}
};
vector<Edge>ET[200];
int DJ[200];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
struct Pq
{
	int u,time;
	Pq(){}
	Pq(const int _u,const int _t):u(_u),time(_t){}
	bool operator<(const Pq &p)const{return time>p.time;}
};
int Solve(const int source,const int target,const int starttime)
{
	priority_queue<Pq>pq;
	pq.push(Pq(source,starttime));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.u==target)return p.time;
		for(const Edge &e:ET[p.u])
		{
			int tnxt=p.time;
			if(tnxt<e.start)tnxt=e.start;
			else tnxt=e.start+((tnxt-e.start)/5+1)*5;
			pq.push(Pq(e.to,tnxt+e.cost));
		}
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		LINE.clear();
		IDX.clear();
		for(int i=0,a,cnt,b,sz=0;i<N;i++)
		{
			static Line line;
			scanf("%d%d",&line.idx,&line.cnt);
			vector<int>&time=line.time;
			time.clear();
			for(int j=1;j<=cnt;j++)
			{
				scanf("%d",&b);
				if(j>1)b=time[j-2]+b;
				time.push_back(b+1);
				IDX[Pair(a,j)]=sz++;
			}
			LINE.push_back(line);
		}
		assert(IDX.size()<=N*20);
		for(int i=0;i<IDX.size();i++)DJ[i]=i;
		for(int i=0,a1,b1,a2,b2;i<M;i++)
		{
			scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
			DJ[Find(IDX[Pair(a1,b1)])]=Find(IDX[Pair(a2,b2)]);
		}
		for(auto &it:IDX)it.second=Find(it.second);
		for(int i=0;i<IDX.size();i++)ET[i].clear();
		for(const auto line:LINE)
		{
			for(int i=1;i+1<=line.time.size();i++)ET[IDX[Pair(line.idx,i)]].push_back(Edge(IDX[Pair(line.idx,i+1)],line.time[i+1]-line.time[i],line.time[i]));
			for(int i=line.time.size();i-1>=1;i--)ET[IDX[Pair(line.idx,i)]].push_back(Edge(IDX[Pair(line.idx,i-1)],line.time[i]-line.time[i-1],line.time[i]));
		}
		for(int remain=5,h,m,i,p,j,q;remain--;)
		{
			scanf("%d%d%d%d%d%d",&h,&m,&i,&p,&j,&q);
			printf("%d\n",Solve(IDX[Pair(i,p)],IDX[Pair(j,q)],h*60+m));
		}
	}
	return 0;
}
