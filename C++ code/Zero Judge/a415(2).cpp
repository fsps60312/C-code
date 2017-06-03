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
	int to,cost;
	Edge(){}
	Edge(const int _t,const int _c):to(_t),cost(_c){}
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
int Solve(const int source,const int target)
{
	priority_queue<Pq>pq;
	pq.push(Pq(source,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.u==target)return p.time;
		for(const Edge &e:ET[p.u])
		{
			pq.push(Pq(e.to,p.time+1+e.cost));
		}
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		LINE.clear();
		IDX.clear();
		for(int i=0,b,sz=0;i<N;i++)
		{
			Line line;
			scanf("%d%d",&line.idx,&line.cnt);
			vector<int>&time=line.time;
			for(int j=0;j<line.cnt;j++)
			{
				scanf("%d",&b);
				time.push_back(b);
				IDX[Pair(line.idx,j)]=sz++;
			}
			LINE.push_back(line);
		}
		assert(IDX.size()<=N*20);
		for(int i=0;i<IDX.size();i++)DJ[i]=i;
		for(int i=0,a1,b1,a2,b2;i<M;i++)
		{
			scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
			DJ[Find(IDX[Pair(a1,--b1)])]=Find(IDX[Pair(a2,--b2)]);
		}
		for(auto &it:IDX)it.second=Find(it.second);
		for(int i=0;i<IDX.size();i++)ET[i].clear();
		for(const auto &line:LINE)
		{
			for(int i=0;i+1<line.time.size();i++)ET[IDX[Pair(line.idx,i)]].push_back(Edge(IDX[Pair(line.idx,i+1)],line.time[i+1]));
			for(int i=line.time.size()-1;i>0;i--)ET[IDX[Pair(line.idx,i)]].push_back(Edge(IDX[Pair(line.idx,i-1)],line.time[i]));
		}
		for(int remain=5,h,m,i,p,j,q;remain--;)
		{
			scanf("%d%d%d%d%d%d",&h,&m,&i,&p,&j,&q);
			printf("%d\n",Solve(IDX[Pair(i,--p)],IDX[Pair(j,--q)]));
		}
	}
	return 0;
}
