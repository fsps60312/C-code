#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M;
vector<int>ET[40000];
void Bfs(const int source,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=INF;
	queue<int>q;
	q.push(source),dist[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(dist[u]+1<dist[nxt])
			{
				dist[nxt]=dist[u]+1;
				q.push(nxt);
			}
		}
	}
}
int DT[40000],DF[40000];
int CNTT[5],CNTF[5];
int CNTS[5][5];
typedef long long LL;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		Bfs(0,DT);
		Bfs(1,DF);
		for(int i=0;i<5;i++)CNTT[i]=CNTF[i]=0;
		for(int i=0;i<5;i++)for(int j=0;j<5;j++)CNTS[i][j]=0;
		for(int i=0;i<N;i++)++CNTT[min(4,DT[i])],++CNTF[min(4,DF[i])],++CNTS[min(4,DT[i])][min(4,DF[i])];
		for(int i=0;i<5;i++)printf("%d %d\n",CNTT[i],CNTF[i]);
		LL ans=0LL;
		for(int i=0;i<5;i++)
		{
			for(int j=4-i;j<5;j++)ans+=(LL)CNTT[i]*CNTF[j]-CNTS[i][j];
		}
		printf("%lld\n",ans-M);
	}
	return 0;
}
