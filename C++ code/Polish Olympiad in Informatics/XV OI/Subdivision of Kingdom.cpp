#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,M;
bool EDGE[26][26],SELECTED[26];
int ANS[26],BEST;
void Dfs(const int u,const int count,const int road)
{
	if(count+(N-u)<N/2)return;
	if(count==N/2)
	{
		if(road<BEST)
		{
			BEST=road;
			int cur=0;
			for(int i=0;i<N;i++)if(SELECTED[i])ANS[cur++]=i;
			assert(cur==N/2);
		}
		return;
	}
	if(u)Dfs(u+1,count,road);
	int nxt_road=road;
	for(int nxt=0;nxt<N;nxt++)if(EDGE[u][nxt])
	{
		if(SELECTED[nxt])--nxt_road;
		else ++nxt_road;
	}
	SELECTED[u]=true;
	Dfs(u+1,count+1,nxt_road);
	SELECTED[u]=false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),--a,--b,EDGE[a][b]=EDGE[b][a]=true;
		for(int i=0;i<N;i++)SELECTED[i]=false;
		BEST=INF;
		Dfs(0,0,0);
		for(int i=0;i<N/2;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]+1);
		}
		puts("");
//		printf("best=%d\n",BEST);
	}
	return 0;
}
