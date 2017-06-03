#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,TYPE[200];
bool EDGE[200][200],ODD[200];
int OddVertex(){for(int i=0;i<N;i++)if(TYPE[i]==-1&&ODD[i])return i;return -1;}
void Dfs()
{
	const int now=OddVertex();
	if(now==-1){for(int i=0;i<N;i++)if(TYPE[i]==-1)TYPE[i]=0;return;}
	vector<int>subgraph;
	for(int i=0;i<N;i++)if(EDGE[now][i])assert(TYPE[i]==-1),subgraph.push_back(i);
	subgraph.push_back(now);
	for(int i=0;i<(int)subgraph.size();i++)for(int j=i+1;j<(int)subgraph.size();j++)
	{
		const int a=subgraph[i],b=subgraph[j];
		assert(a!=b);
		assert(EDGE[a][b]==EDGE[b][a]);
		ODD[a]^=true,ODD[b]^=true;
		EDGE[a][b]^=true,EDGE[b][a]^=true;
	}
	for(int i=0;i<N;i++)assert(!EDGE[now][i]&&!EDGE[i][now]);
	TYPE[now]=-2;
	Dfs();
	subgraph.pop_back();
	assert((int)subgraph.size()%2==1);
	int cnt0=0;
	for(const int nxt:subgraph)
	{
		assert(TYPE[nxt]==0||TYPE[nxt]==1);
		if(TYPE[nxt]==0)cnt0++;
	}
	if(cnt0%2==0)TYPE[now]=0;
	else TYPE[now]=1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
	for(int i=0;i<N;i++)TYPE[i]=-1,ODD[i]=false;
	for(int i=0,cnt,j;i<N;i++)
	{
		scanf(1,"%d",&cnt);
		while(cnt--)scanf(1,"%d",&j),j--,EDGE[i][j]^=true,ODD[i]^=true;
	}
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)assert(EDGE[i][j]==EDGE[j][i]);
	Dfs();
	vector<int>ans;
	for(int i=0;i<N;i++)
	{
		if(TYPE[i]==0)ans.push_back(i);
		else assert(TYPE[i]==1);
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",ans[i]+1);
	}
	puts("");
	return 0;
}
