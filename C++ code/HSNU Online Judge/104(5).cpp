#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int T,N,M,P;
struct Edge
{
	int u,cost;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Edge &e)const{return u!=e.u?u<e.u:cost<e.cost;}
};
int DIST[100][100];
bool Solve()
{
	for(int i=0;i<N;i++)if(DIST[i][i]>0)return true;
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&P);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=-INF;
		for(int i=0;i<N;i++)DIST[i][i]=0;
		for(int i=0;i<M;i++)
		{
			static int a,b,income,afford,cost;
			scanf("%d%d%d%d",&a,&b,&income,&afford);
			cost=income-afford*P;
			DIST[a][b]=max(DIST[a][b],cost);
		}
		for(int m=0;m<N;m++)
		{
			for(int i=0;i<N;i++)
			{
				if(DIST[i][m]==-INF)continue;
				for(int j=0;j<N;j++)
				{
					if(DIST[m][j]==-INF)continue;
					getmax(DIST[i][j],DIST[i][m]+DIST[m][j]);
				}
			}
		}
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
