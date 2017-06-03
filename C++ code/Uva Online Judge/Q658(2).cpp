#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Edge
{
	int require,banned,fixed,introduced;
	LL cost;
	Edge(){}
	Edge(const int _r,const int _b,const int _f,const int _i,const LL &_c):require(_r),banned(_b),fixed(_f),introduced(_i),cost(_c){}
};
vector<Edge>EDGE;
struct Pq
{
	int u;
	LL cost;
	Pq(const int _u,const LL &_c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[1<<20];
int N,M;
LL Solve()
{
	priority_queue<Pq>pq;
	pq.push(Pq((1<<N)-1,0LL));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.u])continue;
		VIS[p.u]=true;
		if(p.u==0)return p.cost;
		for(const Edge &e:EDGE)if((p.u&e.require)==e.require&&(p.u&e.banned)==0)
		{
			pq.push(Pq((p.u&(~e.fixed))|e.introduced,p.cost+e.cost));
		}
	}
	return INF;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&M)==2);
		if(N==0&&M==0)break;
		assert(N>=1&&N<=20);
		for(int i=0;i<(1<<N);i++)VIS[i]=false;
		EDGE.clear();
		while(M--)
		{
			static LL cost;
			static char tmpa[21],tmpb[21];
			assert(scanf("%lld%s%s",&cost,tmpa,tmpb)==3);
			assert(cost>=0LL);
			int require=0,banned=0,fixed=0,introduced=0;
			for(int i=0;i<N;i++)
			{
				if(tmpa[i]=='+')require|=1<<i;
				else if(tmpa[i]=='-')banned|=1<<i;
				else assert(tmpa[i]=='0');
				if(tmpb[i]=='+')introduced|=1<<i;
				else if(tmpb[i]=='-')fixed|=1<<i;
				else assert(tmpb[i]=='0'); 
			}
			EDGE.push_back(Edge(require,banned,fixed,introduced,cost));
		}
		static int kase=1;
		printf("Product %d\n",kase++);
		const LL ans=Solve();
		if(ans==INF)puts("Bugs cannot be fixed.");
		else printf("Fastest sequence takes %lld seconds.\n",ans);
		puts("");
	}
	assert(scanf("%d",&N)!=1);
	return 0;
}
