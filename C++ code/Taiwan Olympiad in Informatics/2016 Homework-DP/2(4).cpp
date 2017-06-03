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
		assert(H[i]>0);
		C1[i]=(H[i]-1)/Q,C2[i]=(((H[i]-1)%Q+1)-1)/P;
	}
	for(int i=0;i<=20000;i++)DP[0][i]=-INF;
	DP[0][1]=0;
	int d=0;
	for(int i=0;i<N;i++,d^=1)
	{
		for(int j=0;j<=20000;j++)DP[d^1][j]=-INF;
		for(int j=0;j<=20000;j++)if(DP[d][j]!=-INF)
		{
			getmax(DP[d^1][j+C1[i]+1],DP[d][j]);
			int remain=j+C1[i]-C2[i]-1;
			if(remain>=0)getmax(DP[d^1][remain],DP[d][j]+G[i]);
		}
	}
	int ans=0;
	for(int j=0;j<=20000;j++)if(DP[d][j]!=-INF)getmax(ans,DP[d][j]);
	printf("%d\n",ans);
	return 0;
}
