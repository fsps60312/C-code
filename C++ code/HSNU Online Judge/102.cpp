#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,DEG[200];
bool EDGE[200][200];
int TYPE[200];
int GetOddVertex()
{
	for(int i=0;i<N;i++)if(TYPE[i]==-1&&DEG[i]%2==1)return i;
	return -1;
}
void Dfs()
{
	const int now=GetOddVertex();
	if(now==-1){for(int i=0;i<N;i++)if(TYPE[i]==-1)TYPE[i]=0;return;}
	TYPE[now]=-2;
	vector<int>neighbor;
	for(int i=0;i<N;i++)if(TYPE[i]==-1&&EDGE[now][i])neighbor.push_back(i);
	for(int i=0;i<N;i++)if(TYPE[i]==-1)
	{
		if(EDGE[now][i])EDGE[now][i]=EDGE[i][now]=false,DEG[now]--,DEG[i]--;
		else EDGE[now][i]=EDGE[i][now]=true,DEG[now]++,DEG[i]++;
	}
	Dfs();
	vector<int>cnt[2];
	assert((int)neighbor.size()%2==1);
	for(const int nxt:neighbor)
	{
		assert(TYPE[nxt]==0||TYPE[nxt]==1);
		cnt[TYPE[nxt]].push_back(nxt);
	}
	printf("now=%d,(%d,%d)\n",now+1,cnt[0].size(),cnt[1].size());
	for(int i=0;i<2;i++){for(int v:cnt[i])printf(" %d",v+1);puts("");}
	if((int)cnt[0].size()%2==0)TYPE[now]=0;
	else assert((int)cnt[1].size()%2==0),TYPE[now]=1;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
	for(int i=0;i<N;i++)DEG[i]=0;
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf(1,"%d",&cnt);
		while(cnt--)scanf(1,"%d",&v),v--,EDGE[i][v]=true,DEG[i]++;
	}
	for(int i=0;i<N;i++)TYPE[i]=-1;
	Dfs();
	vector<int>ans;
	for(int i=0;i<N;i++)
	{
		assert(TYPE[i]==0||TYPE[i]==1);
		if(TYPE[i]==0)ans.push_back(i);
	}
	printf("%d\n",ans.size());
	for(int i=0;i<(int)ans.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",ans[i]+1);
	}
	puts("");
	return 0;
}
