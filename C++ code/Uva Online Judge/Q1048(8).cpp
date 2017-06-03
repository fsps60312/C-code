#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int NT,NI;
map<int,int>IDX,RI;
vector<int>MIN;
vector<int>PRE;
struct Ticket
{
	int cost,idx;
	vector<int>city;
	Ticket(){}
};
vector<vector<Ticket> >AD;
int GetIdx(int i)
{
	if(IDX.find(i)==IDX.end())
	{
		static int sz;
		sz=IDX.size();
		AD.push_back(vector<Ticket>());
		MIN.push_back(INF);
		PRE.push_back(-1);
		RI[sz]=i;
		return IDX[i]=sz++;
	}
	return IDX[i];
}
struct Pq
{
	int u,i,cost,pre;
	Pq(){}
	Pq(int u,int i,int cost,int pre):u(u),i(i),cost(cost),pre(pre){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
Pq solve(vector<int>&trip)
{
	priority_queue<Pq>pq;
//	for(int i=0;i<trip.size();i++)printf(" %d",RI[trip[i]]);puts("");
	pq.push(Pq(trip[0],0,0,-1));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(p.u==trip[p.i])p.i++;
		if(p.i==trip.size())return p;
		if(p.cost<MIN[p.u])MIN[p.u]=p.cost,PRE[p.u]=p.pre;
		else if(p.cost>MIN[p.u])continue;
//		printf("u=%d,i=%d,cost=%d,pre=%d\n",RI[p.u],p.i,p.cost,p.pre);
		for(int i=0;i<AD[p.u].size();i++)
		{
			Ticket &t=AD[p.u][i];
			for(int i=1,j=p.i;i<t.city.size();i++)
			{
				int &c=t.city[i];
				if(c==trip[j])j++;
				pq.push(Pq(t.city[i],j,p.cost+t.cost,t.idx));
			}
		}
	}
	assert(0);
}
vector<int>START;
void PrintAns(int i)
{
	if(i==-1)return;
	PrintAns(PRE[START[i]]);
	printf(" %d",i+1);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&NT)==1&&NT)
	{
		IDX.clear();
		RI.clear();
		MIN.clear(),PRE.clear(),AD.clear();
		START.clear();
		for(int i=0;i<NT;i++)
		{
			static Ticket t;
			t.idx=i;
			static int n,v;
			scanf("%d%d",&t.cost,&n);
			assert(t.cost>0);
			t.city.clear();
			while(n--)
			{
				scanf("%d",&v);
				t.city.push_back(GetIdx(v));
			}
			START.push_back(t.city[0]);
			AD[t.city[0]].push_back(t);
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
				trip.push_back(GetIdx(v));
			}
			Pq ans=solve(trip);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used:",kase,trip_cnt++,ans.cost);
			PrintAns(ans.pre);
			puts("");
		}
	}
	return 0;
}
