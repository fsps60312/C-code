#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,A,G[301][301],SUM[301][301];
int Q(const int &x1,const int &x2,const int &y1,const int &y2)
{
	return SUM[x2][y2]-SUM[x1-1][y2]-SUM[x2][y1-1]+SUM[x1-1][y1-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&A)==2)
	{
		for(int i=0;i<=N;i++)SUM[0][i]=SUM[i][0]=0;
		G[1][1]=A;
		for(int j=2;j<=N;j++)G[1][j]=A+j;
		for(int i=2;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				G[i][j]=(G[i-1][j]*17)%103*((i+j)&1?-1:1);
			}
		}
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+G[i][j];
//				printf(" %d",G[i][j]);
			}
//			puts("");
		}
		int ans=-INF;
		for(int i=1,j,l,r,s;i<=N;i++)
		{
			for(j=i;j<=N;j++)
			{
				l=1;
				for(r=1;r<=N;r++)
				{
					s=Q(i,j,l,r);
					ans=max(ans,s);
					if(s<0)l=r+1;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
