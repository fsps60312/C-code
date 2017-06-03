#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int P,Q,N;
int H[100],G[100],C1[100],C2[100];
int DP[2][200*100+1];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&P,&Q,&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&H[i],&G[i]);
		C1[i]=(H[i]-1)/Q,C2[i]=(((H[i]-1)%Q+1)-1)/P;
	}
	for(int i=0;i<=20000;i++)DP[0][i]=-INF;
	DP[0][0]=0;
	int d=0;
	for(int i=0;i<N;i++,d^=1)
	{
		for(int j=0;j<=20000;j++)DP[d^1][j]=-INF;
		for(int j=0;j<=20000;j++)if(DP[d][j]!=-INF)
		{
			getmax(DP[d^1][j+C1[i]+1],DP[d][j]);
			int remain=j;
			int dis=min(remain,C2[i]);
			remain-=dis;
			int nxtc2=C2[i]-dis;
			dis=min(C1[i],nxtc2);
			nxtc2-=dis;
			int nxtc1=C1[i]-dis;
			if(nxtc2==0)remain+=nxtc1,getmax(DP[d^1][remain],DP[d][j]+G[i]);
//			int remain=DP[d][j];
//			int dis=min(remain,C2[i]);
//			int nxtc2=C2[i]-dis;
//			if(nxtc2<=C2[i])getmax(DP[d^1][j+G[i]],remain-dis-nxtc2-1+C1[i]);
		}
	}
	int ans=0;
	for(int i=0;i<=20000;i++)if(DP[d][i]!=-INF)getmax(ans,DP[d][i]);
	printf("%d\n",ans);
	return 0;
}
