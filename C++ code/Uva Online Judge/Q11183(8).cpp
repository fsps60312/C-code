#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(int a,int b,int cost):a(a),b(b),cost(cost){}
};
Edge EDGE[40000];
int ID[1000],COST[1000],FA[1000],VIS[1000];
int Solve()
{
	int ans=0,root=0;
	for(;;)
	{
		for(int i=0;i<N;i++)ID[i]=-1,FA[i]=-1,COST[i]=INF,VIS[i]=-1;
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b,&cost=EDGE[i].cost;
			if(b!=root&&cost<COST[b])COST[b]=cost,FA[b]=a;
		}
		for(int i=0;i<N;i++)
		{
			if(i==root)continue;
			if(FA[i]==-1)return -1;
			ans+=COST[i];
		}
		int cnt=0;
		for(int i=0;i<N;i++)
		{
			if(VIS[i]!=-1)continue;
			static int u;
//			puts("a");
			for(u=i;u!=root&&VIS[u]==-1;u=FA[u])VIS[u]=i;
//			puts("b");
			if(u==root||VIS[u]!=i)continue;
//			puts("c");
			for(int j=FA[u];j!=u;j=FA[j])ID[j]=cnt;
//			puts("d");
			ID[u]=cnt++;
		}
//		printf("cnt=%d\n",cnt);
		if(!cnt)return ans;
		for(int i=0;i<N;i++)if(ID[i]==-1)ID[i]=cnt++;
		N=cnt;
		for(int i=0;i<M;)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b,&cost=EDGE[i].cost;
			if(ID[a]==ID[b])EDGE[i]=EDGE[--M];
			else
			{
				cost-=COST[b];
				a=ID[a],b=ID[b];
				i++;
			}
		}
		root=ID[root];
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<1000;i++)VIS[i]=0;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<M;i++)
			{
				static int a,b,cost;
				scanf("%d%d%d",&a,&b,&cost);
				EDGE[i]=Edge(a,b,cost);
			}
			static int kase=1;
			printf("Case #%d: ",kase++);
			int ans=Solve();
			if(ans==-1)puts("Possums!");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
/*
4

2 1
0 1 10

2 1
1 0 10

4 4
0 1 10
0 2 10
1 3 20
2 3 30

4 4
0 1 10
1 2 20
2 0 30
2 3 100
*/
