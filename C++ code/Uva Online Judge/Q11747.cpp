#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
struct Edge
{
	int a,b,w;
	Edge(){}
	Edge(const int _a,const int _b,const int _w):a(_a),b(_b),w(_w){}
	bool operator<(const Edge &e)const{return w<e.w;}
};
vector<Edge>EDGE;
int N,M,DJ[1000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		EDGE.clear();
		for(int i=0,a,b,w;i<M;i++)scanf("%d%d%d",&a,&b,&w),EDGE.push_back(Edge(a,b,w));
		sort(EDGE.begin(),EDGE.end());
		vector<int>ans;
		for(const Edge &e:EDGE)
		{
			const int a=Find(e.a),b=Find(e.b);
			if(a==b)ans.push_back(e.w);
			else DJ[a]=b;
		}
		if(ans.empty())puts("forest");
		else
		{
			bool printed=false;
			for(const int v:ans)
			{
				if(printed)putchar(' ');
				printf("%d",v);
				printed=true;
			}
			puts("");
		}
	}
	return 0;
}
