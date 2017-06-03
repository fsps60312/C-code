#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
int DJ[50000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;DJ[a]=b;return true;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)DJ[i]=i;
	EDGE.clear();
	for(int i=0;i<M;i++)
	{
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c),a--,b--;
		EDGE.push_back(Edge(a,b,c));
	}
	sort(EDGE.begin(),EDGE.end());
	int cnt=N,cost=0;
	for(const Edge &e:EDGE)
	{
		if(!Merge(e.a,e.b))continue;
		cost+=e.cost;
		if(--cnt==1)break;
	}
	if(cnt==1)printf("%d\n",cost);
	else puts("-1");
	return 0;
}
