#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
int R[15],C[15];
struct Edge
{
	int to,w;
	Edge(){}
	Edge(int to,int w):to(to),w(w){}
};
vector<Edge>LR[15],RL[15];
void BuildEdge(int *r,int *c)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			int w=abs(R[i]-r[j])+abs(C[i]-c[j]);
			LR[i].push_back(Edge(j,w));
			RL[j].push_back(Edge(i,w));
		}
	}
}
int Solve()
{
	for(int i=0;i<N;i++)
	{
		R[i]=L[i]=0;
		for(int j=0;j<LR[i].size();j++)
		{
			L[i]=max(L[i],LR[i][j].w);
		}
	}
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&R[i],&C[i]);
		int ans=INF;
		for(int t=0;t<N;t++)
		{
			static int r[15],c[15];
			for(int i=0;i<N;i++)
			{
				r[i]=t;
				c[i]=i;
				LR[i].clear(),RL[i].clear();
			}
			BuildEdge();
			int ta=Solve();
			ans=min(ans,ta);
		}
	}
	return 0;
}
