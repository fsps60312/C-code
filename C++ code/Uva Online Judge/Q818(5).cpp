#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,CNT[15][15],ANS,DEG[15],VIS[15];
vector<int>TO[15];
void dfs(int u,int now,int dep)
{
	if(VIS[u])return;
	
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		static bool vis[15][15];
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			DEG[i]=0;
			VIS[i]=false;
			for(int j=0;j<N;j++)vis[i][j]=0;
		}
		ANS=INF;
		for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1||b==-1);)
		{
			a--,b--;
			DEG[a]++,DEG[b]++;
			if(vis[a][b])continue;
			vis[a][b]=vis[b][a]=true;
			TO[a].push_back(b);
			TO[b].push_back(a);
		}
		for(int i=0;i<N;i++)
		{
			dfs(i);
		}
		int kase=1;
		printf("Set %d: Minimum links to open is %d\n",kase++,ANS);
	}
	return 0;
}
