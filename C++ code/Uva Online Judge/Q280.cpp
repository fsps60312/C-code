#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,PRE[101],VIS[101];
vector<int> LINK[101],ANS[101];
void init()
{
	for(int i=1;i<=N;i++)
	{
		LINK[i].clear();
		PRE[i]=0;
	}
	int i;
	while(scanf("%d",&i)==1&&i)
	{
		int j;
		while(scanf("%d",&j)==1&&j)
		{
			LINK[i].push_back(j);
		}
	}
}
void getans(int u)
{
	if(!PRE[u])
	{
		for(int i=1;i<=N;i++)VIS[i]=0;
		queue<int> q;
		for(int i=0;i<LINK[u].size();i++)
		{
			q.push(LINK[u][i]);
		}
		while(!q.empty())
		{
			int tu=q.front();q.pop();
			if(VIS[tu])continue;
			VIS[tu]=true;
			for(int i=0;i<LINK[tu].size();i++)q.push(LINK[tu][i]);
		}
		ANS[u].clear();
		for(int i=1;i<=N;i++)if(!VIS[i])ANS[u].push_back(i);
		PRE[u]=1;
	}
	printf("%d",ANS[u].size());
	for(int i=0;i<ANS[u].size();i++)printf(" %d",ANS[u][i]);
	printf("\n");
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		init();
		int q;scanf("%d",&q);
		while(q--)
		{
			int a;scanf("%d",&a);
			getans(a);
		}
	}
	return 0;
}
