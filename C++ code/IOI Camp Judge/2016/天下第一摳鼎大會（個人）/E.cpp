#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int MOD=10000,INF=2147483647;
int R,C;
char GRID[1002][1002];
int FIRE[1002][1002];
bool VIS[1002][1002];
void FireGo()
{
	queue<int>q;
	for(int i=0;i<=R+1;i++)for(int j=0;j<=C+1;j++)FIRE[i][j]=INF,VIS[i][j]=false;
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)if(GRID[i][j]=='F')q.push(i*MOD+j),q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		const int dist=q.front();q.pop();
		const int nowr=u/MOD,nowc=u%MOD;
		if(true)
		{
			const char c=GRID[nowr][nowc];
			if(!c||c=='#')continue;
			if(VIS[nowr][nowc])continue;
			VIS[nowr][nowc]=true;
		}
		FIRE[nowr][nowc]=dist;
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			const int nxtr=nowr+d[i][0],nxtc=nowc+d[i][1];
			q.push(nxtr*MOD+nxtc),q.push(dist+1);
		}
	}
}
int Solve(const int source)
{
	for(int i=0;i<=R+1;i++)for(int j=0;j<=C+1;j++)VIS[i][j]=false;
	queue<int>q;q.push(source),q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		const int dist=q.front();q.pop();
		const int nowr=u/MOD,nowc=u%MOD;
		if(true)
		{
			const char c=GRID[nowr][nowc];
			if(c=='#'||FIRE[nowr][nowc]<=dist)continue;
			if(VIS[nowr][nowc])continue;
			VIS[nowr][nowc]=true;
			if(!c)return dist;
		}
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			const int nxtr=nowr+d[i][0],nxtc=nowc+d[i][1];
			q.push(nxtr*MOD+nxtc),q.push(dist+1);
		}
	}
	return -1;
}
int Solve()
{
	int ans=0;
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)if(GRID[i][j]=='J')
	{
		const int ta=Solve(i*MOD+j);
		if(ta==-1)return -1;
		else if(ta>ans)ans=ta;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&R,&C);
		for(int i=1;i<=R;i++)scanf("%s",GRID[i]+1);
		for(int i=1;i<=R;i++)GRID[i][0]=GRID[i][C+1]=0;
		for(int i=1;i<=C;i++)GRID[0][i]=GRID[R+1][i]=0;
		FireGo();
//		for(int i=1;i<=R;i++)
//		{
//			for(int j=1;j<=C;j++)printf("%2d",FIRE[i][j]);puts("");
//		}
		printf("%d\n",Solve());
	}
	return 0;
}
