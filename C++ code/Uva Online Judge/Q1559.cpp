#include<cstdio>
#include<cassert>
using namespace std;
int N,S,M[20],DP[20][1<<13];
int Win(const int player,const int stone)
{
	assert(stone>=0);
	int &dp=DP[player][stone];
	if(dp!=-1)return dp;
	if(stone==0)return dp=1;
	for(int i=1;i<=M[player]&&i<=stone;i++)if(Win((player+1)%(N*2),stone-i)==0)return dp=1;
	return dp=0;
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&S);
		for(int i=0;i<N*2;i++)scanf("%d",&M[i]);
		for(int i=0;i<N*2;i++)for(int j=0;j<=S;j++)DP[i][j]=-1;
		printf("%d\n",Win(0,S));
	}
	return 0;
}
