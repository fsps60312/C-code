#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
vector<int>AD[30];
int W[30];
struct Point
{
	int r,c;
	Point(){}
	Point(int r,int c):r(r),c(c){}
}P[30];
struct Edge
{
	int a,b,w;
	bool inuse;
	Edge(){}
	Edge(int a,int b,int w):a(a),b(b),w(w),inuse(false){}
};
vector<Edge>EDGE;
void BuildEdge()
{
	for(int i=0;i<N;i++)
	{
		for(int j=N;j<N*2;j++)
		{
			int w=abs(P[i].r-P[j].r)+abs(P[i].c-P[j].c);
			int sz=EDGE.size();
			EDGE.push_back(Edge(i,j,w));
			AD[i].push_back(sz);
			AD[j].push_back(sz);
		}
	}
	for(int i=0;i<N;i++)
	{
		W[i]=W[N+i]=0;
		for(int j=0;j<AD[i].size();j++)
		{
			W[i]=max(W[i],EDGE[AD[i][j]].w);
		}
	}
}
int VIS[30];
int Solve()
{
	static int kase=0;
	for(int i=0;i<N;i++)
	{
		kase++;
		
	}
}
int main()
{
	for(int i=0;i<30;i++)VIS[i]=0;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			a--,b--;
			P[i]=Point(a,b);
		}
		int ans=INF;
		for(int t=0;t<N;t++)
		{
			for(int i=0;i<N;i++)
			{
				AD[i].clear(),AD[N+i].clear();
				P[i+N]=Point(t,i);
			}
			EDGE.clear();
			BuildEdge();
			int ta=Solve();
			ans=min(ans,ta);
		}
		static int kase=0;
		kase++;
		printf("Board %d: %d moves required.\n\n",kase,ans);
	}
	return 0;
}
