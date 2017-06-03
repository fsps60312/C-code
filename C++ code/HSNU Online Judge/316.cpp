#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
int N,K,DJ[2000];
vector<Edge>EDGE;
int max(int a,int b,int c){return max(abs(a),max(abs(b),abs(c)));}
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	static int x[2000],y[2000],z[2000];
	scanf(2,"%d%d",&N,&K);
	for(int i=0;i<N;i++)scanf(3,"%d%d%d",&x[i],&y[i],&z[i]),DJ[i]=i;
	EDGE.clear();
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)EDGE.push_back(Edge(i,j,max(x[i]-x[j],y[i]-y[j],z[i]-z[j])));
	sort(EDGE.begin(),EDGE.end());
	int ans=0;
	for(const Edge &e:EDGE)
	{
		ans=e.cost;
		const int a=Find(e.a),b=Find(e.b);
		if(a!=b)DJ[a]=b,N--;
		if(N<K)break;
	}
	printf("%d\n",ans);
}
