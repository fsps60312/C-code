#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
const int MOD=20437,INF=2147483647;
int N,TOTAL_DIST,TOTAL_COUNT;
char GRID[101];
int DIST[101],COUNT[101];
bool Solve(const int source,const int target)
{
	for(int i=0;i<N*N;i++)DIST[i]=INF,COUNT[i]=0;
	queue<int>q;q.push(source),DIST[source]=0,COUNT[source]=1;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			const int nxtr=u/N+d[i][0],nxtc=u%N+d[i][1];
			if(nxtr<0||nxtr>=N||nxtc<0||nxtc>=N)continue;
			const int nxtu=nxtr*N+nxtc;
			if(GRID[nxtu]!='.')continue;
			if(DIST[nxtu]!=INF)
			{
				if(DIST[nxtu]==DIST[u]+1)(COUNT[nxtu]+=COUNT[u])%=MOD;
				continue;
			}
			DIST[nxtu]=DIST[u]+1;
			(COUNT[nxtu]+=COUNT[u])%=MOD;
			q.push(nxtu);
		}
	}
	if(DIST[target]==INF)return false;
	TOTAL_DIST+=DIST[target];
	(TOTAL_COUNT*=COUNT[target])%=MOD;
	return true;
}
bool Solve()
{
	vector<pair<char,int> >sites;
	for(int i=0;i<N*N;i++)
	{
		const char c=GRID[i];
		if('A'<=c&&c<='Z')sites.push_back(make_pair(c,i));
	}
	sort(sites.begin(),sites.end());
	GRID[sites[0].second]='.';
	for(int i=1;i<(int)sites.size();i++)
	{
		GRID[sites[i].second]='.';
		if(!Solve(sites[i-1].second,sites[i].second))return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%s",GRID+i*N);
		TOTAL_DIST=0,TOTAL_COUNT=1;
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!Solve())puts("Impossible");
		else printf("%d %d\n",TOTAL_DIST,TOTAL_COUNT);
	}
	return 0;
}
