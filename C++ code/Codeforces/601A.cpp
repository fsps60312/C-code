#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,DIST[800];
vector<int>ET[400];
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
		for(int i=0;i<N*2;i++)DIST[i]=INF;
		queue<int>q;
		DIST[0]=0,q.push(0);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const int v:ET[u/2])
			{
				const int nxt=v*2+((u&1)^1);
				if(DIST[nxt]==INF)
				{
					DIST[nxt]=DIST[u]+1;
					q.push(nxt);
				}
			}
		}
		if(DIST[(N-1)*2]==INF)puts("-1");
		else printf("%d\n",max(DIST[(N-1)*2]/2,min(DIST[(N-1)*2],DIST[(N-1)*2+1])));
	}
	return 0;
}
