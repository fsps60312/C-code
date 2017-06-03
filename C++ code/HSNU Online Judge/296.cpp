#include<cstdio>
#include<queue>
using namespace std;
int N,M,S[350];
int C[4];
int DP[41][41][41][41];
bool VIS[41][41][41][41];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<4;i++)C[i]=0;
	for(int i=0,v;i<M;i++)scanf("%d",&v),C[--v]++;
	for(int i=0;i<=C[0];i++)for(int j=0;j<=C[1];j++)for(int k=0;k<=C[2];k++)for(int l=0;l<=C[3];l++)DP[i][j][k][l]=S[0],VIS[i][j][k][l]=false;
	queue<int>q;
	for(int i=0;i<4;i++)q.push(0);
	while(!q.empty())
	{
		static int u[4];
		for(int i=0;i<4;i++)u[i]=q.front(),q.pop();
		bool &vis=VIS[u[0]][u[1]][u[2]][u[3]];
		if(vis)continue;
		vis=true;
		const int dp=DP[u[0]][u[1]][u[2]][u[3]];
//		printf("(%d,%d,%d,%d)=%d\n",u[0],u[1],u[2],u[3],dp);
		for(int i=0;i<4;i++)if(u[i]+1<=C[i])
		{
			u[i]++;
			int &nxtdp=DP[u[0]][u[1]][u[2]][u[3]];
			const int score=dp+S[1*u[0]+2*u[1]+3*u[2]+4*u[3]];
			if(nxtdp<score)
			{
				nxtdp=score;
				for(int j=0;j<4;j++)q.push(u[j]);
			}
			u[i]--;
		}
	}
	printf("%d\n",DP[C[0]][C[1]][C[2]][C[3]]);
	return 0;
}
