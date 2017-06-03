#include<cstdio>
#include<vector>
using namespace std;
int N,S[100000],COLOR[100000];
vector<int>ET[100000];
bool Dfs(const int u,const int c)
{
	if(COLOR[u]!=-1)return COLOR[u]==c;
	COLOR[u]=c;
	for(const int nxt:ET[u])if(!Dfs(nxt,c^1))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)COLOR[i]=-1;
	for(int i=0;i<N;i++)if(COLOR[i]==-1)if(!Dfs(i,0))return false;
	return true;
}
int main()
{
	freopen("inn.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&S[i]),S[i]--;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
		{
			if(S[i]>S[j])ET[S[i]].push_back(S[j]),ET[S[j]].push_back(S[i]),printf("(%d,%d)\n",S[i],S[j]);
		}
		if(Solve())
		{
			puts("TAK");
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%d",COLOR[S[i]]+1);
			}
			puts("");
		}
		else puts("NIE");
	}
	return 0;
}
