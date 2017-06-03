#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N;
int GRID[4][4];
int COLOR[4][4];
int CNT[4];
int ANS;
void Dfs(const int loc,int match)
{
	if(match>=ANS)return;
	const int row=loc/N,column=loc%N;
	if(row==N){ANS=min(ANS,match);return;}
	for(int color=0;color<N;color++)if(CNT[color])
	{
		CNT[color]--;
		COLOR[row][column]=color;
		int add=0;
		if(row)add+=GRID[color][COLOR[row-1][column]]^1;
		if(column)add+=GRID[color][COLOR[row][column-1]]^1;
		Dfs(loc+1,match+add);
		CNT[color]++;
	}
}
int main()
{
//	freopen("H.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&GRID[i][j]);
		for(int i=0;i<N;i++)CNT[i]=N;
		ANS=INF;
		Dfs(0,0);
		printf("%d\n",N*(N-1)*2-ANS);
		break;
	}
	return 0;
}
