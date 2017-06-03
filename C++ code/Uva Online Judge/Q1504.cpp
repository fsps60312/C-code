#include<cstdio>
#include<map>
#include<algorithm>
#include<cassert>
using namespace std;
int N,M,DJ[3000];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
struct Edge
{
	int a,b;
	double cost;
	Edge(){}
	Edge(int a,int b,double c):a(min(a,b)),b(max(a,b)),cost(c){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
}EDGE[3000*3000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		map<Edge,int>edge;
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static double c;
			scanf("%d%d%lf",&a,&b,&c);
			EDGE[i]=Edge(a,b,c);
			edge[EDGE[i]]=i;
		}
		int cnt;
		scanf("%d",&cnt);
		double p=1.0/cnt;
		for(int i=0;i<cnt;i++)
		{
			static int a,b;
			static double c;
			scanf("%d%d%lf",&a,&b,&c);
			Edge e=Edge(a,b,c);
			assert(edge.find(e)!=edge.end());
			int j=edge[e];
			EDGE[j].cost=EDGE[j].cost*(1.0-p)+c*p;
		}
		sort(EDGE,EDGE+M);
		for(int i=0;i<M;i++)printf("%d %d %.4f\n",EDGE[i].a,EDGE[i].b,EDGE[i].cost);
		for(int i=0;i<N;i++)DJ[i]=i;
		double ans=0.0;
		cnt=N;
		for(int i=0;cnt!=1;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b;
			if(FindDJ(a)==FindDJ(b))continue;
			DJ[FindDJ(a)]=FindDJ(b);
			ans+=EDGE[i].cost;
			cnt--;
		}
		printf("%.4f\n",ans);
	}
	return 0;
}
