#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define int long long
const int INF=2147483647;
void getmin(int &a,int b){if(b<a)a=b;} 
int T,M,I;
struct Month
{
	int m,n,p,s,e;
}MONTH[100];
struct Point
{
	int x,y;
	bool operator<(Point a)const{return x<a.x;}
};
struct Edge
{
	int from,to,limit,flow,cost;
};
vector<Edge> EDGE;
vector<int> GETO[1+100+100+1];
int Is(){return M*2;}
int It(){return M*2+1;}
int In(int tosold,int m){return m+tosold*M;}
void add_EDGE(int a,int b,int l,int c)
{
	//printf("add_EDGE(%lld,%lld,%lld,%lld)\n",a,b,l,c);
	GETO[a].push_back(EDGE.size());
	EDGE.push_back((Edge){a,b,l,0,c});
	GETO[b].push_back(EDGE.size());
	EDGE.push_back((Edge){b,a,0,0,-c}); 
}
int INQ[202],PRE[202],COST[202];
bool BellmanFord(int &ans)
{
	for(int i=0;i<=It();i++)
	{
		INQ[i]=0;
		COST[i]=INF;
	}
	queue<int> q;
	q.push(Is());
	INQ[Is()]=1;
	COST[Is()]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=0;
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]];
			if(e.flow==e.limit)continue;
			if(COST[u]+e.cost>=COST[e.to])continue;
			PRE[e.to]=GETO[u][i];
			COST[e.to]=COST[u]+e.cost;
			if(INQ[e.to])continue;
			INQ[e.to]=1;
			q.push(e.to);
		}
	}
	if(COST[It()]>=0)return false;
	int x=It(),low=INF;
	while(x!=Is())
	{
		Edge &e=EDGE[PRE[x]];
		getmin(low,e.limit-e.flow);
		x=e.from;
	}
	x=It();
	while(x!=Is())
	{
		EDGE[PRE[x]].flow+=low;
		EDGE[PRE[x]^1].flow-=low;
		ans-=EDGE[PRE[x]].cost*low;
		x=EDGE[PRE[x]].from;
	}
	return true;
}
#undef int
int main()
{
	#define int long long
	//freopen("in.txt","r",stdin); 
	scanf("%lld",&T);
	int kase=1;
	while(T--)
	{
		scanf("%lld%lld",&M,&I);
		for(int i=0;i<M;i++)
		{
			Month &m=MONTH[i];
			scanf("%lld%lld%lld%lld%lld",&m.m,&m.n,&m.p,&m.s,&m.e);
		}
		EDGE.clear();
		for(int i=0;i<=It();i++)GETO[i].clear();
		for(int i=0;i<M;i++)
		{
			Month &m=MONTH[i];
			add_EDGE(Is(),In(0,i),m.n,m.m);
			add_EDGE(In(1,i),It(),m.s,-m.p);
			for(int j=0;j<=m.e&&i+j<M;j++)
			{
				add_EDGE(In(0,i),In(1,i+j),INF,j*I);
			}
		}
		int ans=0;
		while(BellmanFord(ans));
		printf("Case %lld: %lld\n",kase++,ans);
//		for(int i=0;i<EDGE.size();i+=2)
//		{
//			Edge &e=EDGE[i];
//			printf("EDGE(%lld,%lld):%lld/%lld cost %lld\n",e.from,e.to,e.flow,e.limit,e.cost);
//		}
	}
	return 0;
}
