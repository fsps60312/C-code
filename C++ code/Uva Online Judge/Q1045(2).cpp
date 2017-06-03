#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
vector<int>A[15],B[15];
int LA[15],LB[15];
struct Point
{
	int r,c;
	Point(){}
	Point(int r,int c):r(r),c(c){}
}S[15],T[15];
struct Edge
{
	int a,b,w;
	bool inuse;
	Edge(){}
	Edge(int a,int b,int w):a(a),b(b),w(w),inuse(false){}
};
vector<Edge>EDGE;
void BuildEdge(int *r,int *c)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			int w=abs(S[i].r-T[j].r)+abs(S[i].c-T[j].c);
			int sz=EDGE.size();
			EDGE.push_back(Edge(i,j,w));
			LA[i].push_back(sz);
			LB[j].push_back(sz);
		}
	}
	for(int i=0;i<N;i++)
	{
		R[i]=L[i]=0;
		for(int j=0;j<LR[i].size();j++)
		{
			L[i]=max(L[i],LR[i][j].w);
		}
	}
}
int Solve()
{
	for(int i=0;i<N;i++)
	{
		
	}
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			S[i]=Point(a,b);
		}
		int ans=INF;
		for(int t=0;t<N;t++)
		{
			static int r[15],c[15];
			for(int i=0;i<N;i++)
			{
				LR[i].clear(),RL[i].clear();
				T[i]=Point(t,i);
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
