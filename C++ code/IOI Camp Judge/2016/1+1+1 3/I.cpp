#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
int DJ[10000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;DJ[a]=b;return true;}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)DJ[i]=i;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			EDGE.push_back(Edge(a,b,c));
		}
		sort(EDGE.begin(),EDGE.end());
		LL ans=0LL;
		for(const Edge &e:EDGE)if(Merge(e.a,e.b))ans+=e.cost;
		for(int i=1;i<N;i++)assert(Find(i)==Find(0));
		printf("%lld\n",ans);
	}
	return 0;
}
