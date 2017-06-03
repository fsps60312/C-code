#include<cstdio>
#include<cassert>
#include<string>
#include<map>
#include<queue>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
map<string,int>IDX;
struct Edge
{
	int to;
	LL cost;
	Edge(){}
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
};
vector<Edge>ET[100];
int N,M;
int GetIdx(const string &s)
{
	const auto it=IDX.find(s);
	if(it!=IDX.end())return it->second;
	assert(N<100);
	ET[N].clear();
	return IDX[s]=N++;
}
struct Pq
{
	int u,cnt;
	LL cost;
	Pq(){}
	Pq(const int _u,const int _cnt,const LL &_cost):u(_u),cnt(_cnt),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
LL Solve(const int transfer)
{
	static int vis[100];
	for(int i=0;i<N;i++)vis[i]=2147483647;
	priority_queue<Pq>pq;
	pq.push(Pq(0,1,0LL));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.u==1)return p.cost;
		if(p.cnt>=vis[p.u]||p.cnt>=transfer+2)continue;
		vis[p.u]=p.cnt;
		for(const Edge &e:ET[p.u])pq.push(Pq(e.to,p.cnt+1,p.cost+e.cost));
	}
	return INF;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d",&M)==1);
		while(M--){static char tmp[21];assert(scanf("%s",tmp)==1);}
		assert(scanf("%d",&M)==1);
		IDX.clear(),N=0;
		GetIdx("Calgary"),GetIdx("Fredericton"); 
		for(int i=0;i<M;i++)
		{
			static LL cost;
			static char name1[21],name2[21];
			assert(scanf("%s%s%lld",name1,name2,&cost)==3);
			ET[GetIdx(name1)].push_back(Edge(GetIdx(name2),cost));
		}
		static int querycount;assert(scanf("%d",&querycount)==1);
		static int kase=1;
		if(kase>1)puts("");
		printf("Scenario #%d\n",kase++);
		while(querycount--)
		{
			static int transfer;assert(scanf("%d",&transfer)==1);
			const LL ans=Solve(transfer);
			if(ans==INF)puts("No satisfactory flights");
			else printf("Total cost of flight(s) is $%lld\n",ans);
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
