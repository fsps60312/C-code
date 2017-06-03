#include<cstdio>
#include<cstdlib>
#include<algorithm>
const int INF=1<<30;
using namespace std;
int T,N,D,H[100],XN,X[20000],DP[100][20000];//money cost when move stone i to height j
void getmin(int &a,int b){if(b<a)a=b;}
int abs(int a){return a>=0?a:-a;}
void get_X()
{
	int k=0;
	for(int i=0;i<N;i++)
	{
		for(int j=-N+1;j<N;j++)
		{
			X[k++]=H[i]+j*D;
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
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&D);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&H[i]);
		}
		get_X();
		for(int x=0;x<XN;x++)
		{
			DP[0][x]=X[x]==H[0]?0:INF;
		}
		for(int i=0;i<N-1;i++)
		{
			for(int x=0;x<XN;x++)DP[i+1][x]=INF;
			for(int x=0;x<XN;x++)
			{
				int &dp=DP[i][x];
				if(dp==INF)continue;
				for(int y=x;y<XN&&X[y]-X[x]<=D;y++)
				{
					getmin(DP[i+1][y],dp+abs(H[i+1]-X[y]));
				}
				for(int y=x-1;y>=0&&X[x]-X[y]<=D;y--)
				{
					getmin(DP[i+1][y],dp+abs(X[y]-H[i+1]));
				}
			}
		}
		for(int x=0;x<XN;x++)printf("%5d",X[x]);printf("\n");
		for(int h=0;h<N;h++)
		{
			for(int x=0;x<XN;x++)
			{
				printf("%5d",DP[h][x]==INF?-1:DP[h][x]);
			}printf("\n");
		}
		int ans=INF;
		for(int i=0;i<XN;i++)
		{
			if(X[i]==H[N-1])
			{
				ans=DP[N-1][i];
				break;
			}
		}
		if(ans==INF)printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
