#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
typedef long long LL;
int N,M;
LL W[50000];
struct Edge
{
	int a,b;
	LL c;
	Edge(){}
	Edge(const int &_a,const int &_b,const LL &_c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[50000];
struct Pq
{
	int u;
	LL cost;
	Pq(){}
	Pq(const int &_u,const LL &c):u(_u),cost(c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int VIS[50000],KASE;
LL GetLen(const int &s)
{
	KASE++;
	priority_queue<Pq>pq;
	pq.push(Pq(s,0LL));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.u]==KASE)continue;
		VIS[p.u]=KASE;
		if(p.u==0)return p.cost;
		for(int i=0;i<ET[p.u].size();i++)
		{
			Edge &e=EDGE[ET[p.u][i]];
			pq.push(Pq(e.a==p.u?e.b:e.a,p.cost+e.c));
		}
	}
	return -1LL;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=0;
		EDGE.clear();
		KASE=0;
		for(int i=0;i<N;i++)scanf("%lld",&W[i]);
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static LL c;
			scanf("%d%d%lld",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			ET[b].push_back(i);
		}
		LL ans=0LL;
		for(int i=1;i<N;i++)
		{
			static LL tmp;
			tmp=GetLen(i);
			if(tmp==-1LL){ans=0LL;break;}
			ans+=W[i]*tmp;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
