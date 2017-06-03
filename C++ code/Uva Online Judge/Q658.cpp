#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Edge
{
	int to;
	LL cost;
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
	bool operator<(const Edge &e)const{return cost>e.cost;}
};
vector<Edge>ET[1<<20];
bool VIS[1<<20];
int N,M;
//void Print(const int a){for(int i=0;i<N;i++)putchar(a&(1<<i)?'+':'-');}
LL Solve()
{
	priority_queue<Edge>pq;
	pq.push(Edge((1<<N)-1,0LL));
	while(!pq.empty())
	{
		const Edge p=pq.top();pq.pop();
		if(VIS[p.to])continue;
		VIS[p.to]=true;
//		Print(p.to),printf(" %lld\n",p.cost);
		if(p.to==0)return p.cost;
		for(const Edge &e:ET[p.to])pq.push(Edge(e.to,p.cost+e.cost));
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
		for(int i=0;i<(1<<N);i++)ET[i].clear(),VIS[i]=false;
		while(M--)
		{
			static LL cost;
			static char tmpa[21],tmpb[21];
			assert(scanf("%lld%s%s",&cost,tmpa,tmpb)==3);
			assert(cost>=0LL);
			vector<int>free;
			int require=0,fixed=0,introduced=0;
			for(int i=0;i<N;i++)
			{
				if(tmpa[i]=='0')free.push_back(i);
				else if(tmpa[i]=='+')require|=1<<i;
				else assert(tmpa[i]=='-');
				if(tmpb[i]=='+')introduced|=1<<i;
				else if(tmpb[i]=='-')fixed|=1<<i;
				else assert(tmpb[i]=='0'); 
			}
			const int n=free.size();
			for(int i=0;i<(1<<n);i++)
			{
				int s=require;
				for(int j=0;j<n;j++)if(i&(1<<j))s|=1<<free[j];
				ET[s].push_back(Edge((s&(~fixed))|introduced,cost));
			}
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
