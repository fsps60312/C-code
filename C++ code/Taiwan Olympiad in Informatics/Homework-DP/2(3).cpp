#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int P,Q,N;
int H[100],G[100],C1[100],C2[100];
int DP[101][2][200*100+1];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&P,&Q,&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&H[i],&G[i]);
		C1[i]=(H[i]-1)/Q,C2[i]=(((H[i]-1)%Q+1)-1)/P;
	}
	for(int i=0;i<=20000;i++)DP[0][0][i]=DP[0][1][i]=-INF;
	DP[0][1][0]=DP[0][0][1]=0;
	int d=0;
	for(int i=0;i<N;i++,d++)
	{
		for(int j=0;j<=20000;j++)DP[d+1][0][j]=DP[d+1][1][j]=-INF;
		for(int j=0;j<=20000;j++)
		{
			if(DP[d][1][j]!=-INF)
			{
				getmax(DP[d+1][1][j+C1[i]+1],DP[d][1][j]);
				int remain=j;
				int dis=min(remain,C2[i]);
				remain-=dis;
				int nxtc2=C2[i]-dis;
				dis=min(C1[i],nxtc2);
				nxtc2-=dis;
				int nxtc1=C1[i]-dis;
				if(nxtc2==0)remain+=nxtc1,getmax(DP[d+1][0][remain],DP[d][1][j]+G[i]);
			}
			if(DP[d][0][j]!=-INF)
			{
				getmax(DP[d+1][1][j+C1[i]],DP[d][0][j]);
				if(C1[i]>0)
				{
					int remain=j;
					int dis=min(remain,C2[i]);
					remain-=dis;
					int nxtc2=C2[i]-dis;
					dis=min(C1[i]-1,nxtc2);
					nxtc2-=dis;
					int nxtc1=C1[i]-1-dis;
					if(nxtc2==0)remain+=nxtc1,getmax(DP[d+1][0][remain],DP[d][0][j]+G[i]);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=d;i++)for(int j=0;j<=20000;j++)for(int k=0;k<2;k++)if(DP[i][k][j]!=-INF)getmax(ans,DP[i][k][j]);
//	for(int i=0;i<=20000;i++)if(DP[d][0][i]!=-INF)getmax(ans,DP[d][0][i]),printf("DP[%d,%d,%d]=%d\n",d,0,i,DP[d][0][i]);
//	for(int i=0;i<=20000;i++)if(DP[d][1][i]!=-INF)getmax(ans,DP[d][1][i]),printf("DP[%d,%d,%d]=%d\n",d,1,i,DP[d][1][i]);
	printf("%d\n",ans);
	return 0;
}
