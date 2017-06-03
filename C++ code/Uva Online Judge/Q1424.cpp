#include<cstdio>
#include<cassert>
using namespace std;
void getmin(int &a,const int &b){if(b<a)a=b;}
const int INF=2147483647;
int T,N,M,L,S[200],DP[200];
int DIST[100][100];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=INF;
		for(int i=0;i<N;i++)DIST[i][i]=0;
		for(int i=0;i<M;i++)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			a--,b--;
			DIST[a][b]=DIST[b][a]=1;
		}
		for(int m=0;m<N;m++)
		{
			for(int i=0;i<N;i++)
			{
				if(DIST[i][m]==INF)continue;
				for(int j=0;j<N;j++)
				{
					if(DIST[m][j]==INF)continue;
					getmin(DIST[i][j],DIST[i][m]+DIST[m][j]);
				}
			}
		}
		scanf("%d",&L);
		for(int i=0;i<L;i++){scanf("%d",&S[i]);S[i]--;}
		for(int i=0;i<L;i++)DP[i]=INF;
		DP[0]=0;
		for(int i=1;i<L;i++)
		{
			for(int j=i-1;j>=0;j--)
			{
				if(DP[j]!=INF&&DIST[S[j]][S[i]]<=i-j)getmin(DP[i],DP[j]+i-j-1);
			}
		}
		assert(DP[L-1]!=INF);
		printf("%d\n",DP[L-1]);
	}
	return 0;
}
