#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
const int INF=1<<30;
using namespace std;
int T,N,D,H[100],XN,X[20000],DP[2][20000];//money cost when move stone i to height j
int abs(int a){return a>=0?a:-a;}
void get_X()
{
	int k=0;
	for(int i=0;i<N;i++)
	{
		for(int j=-N+1;j<N;j++)
		{
			int h=H[i]+j*D;
			X[k++]=h;
		}
	}
	sort(X,X+k);
	XN=1;
	for(int i=1;i<k;i++)
	{
		if(X[i-1]==X[i])continue;
		X[XN++]=X[i];
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&D);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&H[i]);
		}
		get_X();
//		for(int i=0;i<XN;i++)printf("%5d",X[i]);puts("");
		for(int i=0;i<XN;i++)DP[0][i]=DP[1][i]=INF;
		queue<int> q[2];
		for(int i=0;i<XN;i++)
		{
			if(X[i]==H[0])
			{
				DP[0][i]=0;
				q[0].push(i);
				break;
			}
		}
		for(int ti=0;ti<N-1;ti++)
		{
			int i=ti&1;
//			for(int j=0;j<XN;j++)printf("%5d",DP[i][j]==INF?-1:DP[i][j]);printf("\n");
			while(!q[i].empty())
			{
				int x=q[i].front();q[i].pop();
				int dp=DP[i][x];
				DP[i][x]=INF;
				for(int y=x;y<XN&&abs(X[x]-X[y])<=D;y++)
				{
					int h=dp+abs(H[ti+1]-X[y]);
					if(h<DP[i^1][y])
					{
						if(DP[i^1][y]==INF)q[i^1].push(y);
						DP[i^1][y]=h;
					}
				}
				for(int y=x-1;y>=0&&abs(X[x]-X[y])<=D;y--)
				{
					int h=dp+abs(H[ti+1]-X[y]);
					if(h<DP[i^1][y])
					{
						if(DP[i^1][y]==INF)q[i^1].push(y);
						DP[i^1][y]=h;
					}
				}
			}
		}
		int ans=INF;
		for(int i=0,h=(N-1)&1;i<XN;i++)
		{
			if(X[i]==H[N-1])
			{
				ans=DP[h][i];
				break;
			}
		}
		if(ans==INF)printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
