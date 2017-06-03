#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,A[100000];
vector<int>ET[100000];
int ANS[100000];
bool Dfs(const int u,const int color)
{
	if(ANS[u]!=-1)return ANS[u]==color;
	ANS[u]=color;
	for(int i=0;i<(int)ET[u].size();i++)if(!Dfs(ET[u][i],color^1))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)ANS[i]=-1;
	for(int i=0;i<N;i++)if(ANS[i]==-1&&!Dfs(i,0))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		for(int i=0;i<N;i++)ET[i].clear();
		static int mn[100000];
		mn[N-1]=A[N-1];
		for(int i=N-2;i>=0;i--)mn[i]=min(mn[i+1],A[i]);
		for(int i=0;i<N;i++)for(int j=i+1;j+1<N;j++)if(mn[j+1]<A[i]&&A[i]<A[j])ET[i].push_back(j),ET[j].push_back(i);
		if(!Solve())puts("NIE");
		else
		{
			puts("TAK");
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[i]+1);
			}
			puts("");
		}
	}
	return 0;
}
