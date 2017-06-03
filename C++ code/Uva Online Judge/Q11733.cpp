#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
int N,M,A;
int DJ[10000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d%d",&N,&M,&A);
		for(int i=0;i<N;i++)DJ[i]=i;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)scanf("%d%d%d",&a,&b,&c),EDGE.push_back(Edge(--a,--b,c));
		sort(EDGE.begin(),EDGE.end());
		int cnt=N,cost=N*A;
		for(const Edge &e:EDGE)
		{
			if(e.cost>=A)break;
			int a=Find(e.a),b=Find(e.b);
			if(a==b)continue;
			DJ[a]=b,cnt--,cost-=A,cost+=e.cost;
		}
		static int kase=1;
		printf("Case #%d: %d %d\n",kase++,cost,cnt);
	}
	return 0;
}
