#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
using namespace std;
struct Hungary
{
	int N,M,MATCH[100];
	bool EDGE[100][100],VIS[100];
	bool Match(const int u)
	{
		for(int nxt=0;nxt<M;nxt++)if(EDGE[u][nxt]&&!VIS[nxt])
		{
			VIS[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int Solve()
	{
		for(int i=0;i<M;i++)MATCH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)VIS[j]=false;
			if(Match(i))++ans;
		}
		return ans;
	}
}HUNGARY;
double SX[100],SY[100],TX[100],TY[100];
double Hypot(const double a,const double b){return sqrt(a*a+b*b);}
double Distance(const int a,const int b){return Hypot(SX[a]-TX[b],SY[a]-TY[b]);}
int S,V;
int main()
{
//	freopen("in.txt","r",stdin);
	int &N=HUNGARY.N,&M=HUNGARY.M;
	while(scanf("%d%d%d%d",&N,&M,&S,&V)==4)
	{
		for(int i=0;i<N;i++)scanf("%lf%lf",&SX[i],&SY[i]);
		for(int i=0;i<M;i++)scanf("%lf%lf",&TX[i],&TY[i]);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)HUNGARY.EDGE[i][j]=(Distance(i,j)/V<=S);
		printf("%d\n",N-HUNGARY.Solve());
	}
	return 0;
}
