#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int NT,NI;
struct Edge
{
	int cost,idx,to;
	Edge(){}
	Edge(int cost,int idx,int to):cost(cost),idx(idx),to(to){}
};
vector<vector<Edge> >AD;
map<int,int>IDX;
vector<int>MIN;
vector<int>PRE;
int GetIdx(int i)
{
	if(IDX.find(i)==IDX.end())
	{
		static int sz;
		sz=IDX.size();
		AD.push_back(vector<Edge>());
		MIN.push_back(INF);
		PRE.push_back(-1);
		return IDX[i]=sz++;
	}
	return IDX[i];
}
struct Pq
{
	int u,i,len,cost,pre;
	Pq(){}
	Pq(int u,int i,int len,int cost,int pre):u(u),i(i),len(len),cost(cost),pre(pre){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:len>p.len;}
};
Pq solve(vector<int>&trip)
{
	priority_queue<Pq>pq;
	pq.push(Pq(trip[0],0,0,0,-1));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(p.u==trip[p.i])p.i++;
		if(p.i==trip.size())return p;
		if(p.cost<MIN[p.u])MIN[p.u]=p.cost,PRE[p.u]=p.pre;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Edge &e=AD[p.u][i];
			pq.push(Pq(e.to,p.i,p.len+1,p.cost+e.cost,e.idx));
		}
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&NT)==1&&NT)
	{
		IDX.clear();
		vector<int>ticket;
		for(int i=0;i<NT;i++)
		{
			static int cost,n,s,v;
			scanf("%d%d%d",&cost,&n,&s);
			ticket.push_back(s);
			while(--n)
			{
				scanf("%d",&v);
				AD[GetIdx(s)].push_back(Edge(cost,i,GetIdx(v)));
			}
		}
		scanf("%d",&NI);
		static int kase=0;
		kase++;
		int trip_cnt=1;
		while(NI--)
		{
			vector<int>trip;
			static int n,v;
			scanf("%d",&n);
			while(n--)
			{
				scanf("%d",&v);
				trip.push_back(v);
			}
			Pq ans=solve(trip);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used: %d\n",kase,trip_cnt++,ans.cost,ans.len);
		}
	}
	return 0;
}
