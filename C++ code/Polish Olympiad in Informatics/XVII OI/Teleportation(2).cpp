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
int main()
{
//	freopen("in.txt","r",stdin);
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
		for(int i=0;i<N;i++)++CNTT[min(4,DT[i])],++CNTF[min(4,DF[i])];
		int ans=0;
		for(int mid_dist=1;mid_dist<=4;mid_dist++)
		{
			int cntm=N,ta=0;
			for(int i=0;i<mid_dist;i++)
			{
				cntm-=CNTT[i];
				ta+=CNTT[i]*(CNTT[i]-1)/2;
				if(i)ta+=CNTT[i]*CNTT[i-1];
			}
			for(int i=0;i+mid_dist<5;i++)
			{
				cntm-=CNTF[i];
				ta+=CNTF[i]*(CNTF[i]-1)/2;
				if(i)ta+=CNTF[i]*CNTF[i-1];
			}
			ta+=cntm*(cntm-1)/2;
			ta+=cntm*CNTT[mid_dist-1];
			ta+=cntm*CNTF[5-mid_dist-1];
			if(ta>ans)ans=ta;
		}
		printf("%d\n",ans-M);
	}
	return 0;
}
