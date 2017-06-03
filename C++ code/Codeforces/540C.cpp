#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,M,R1,C1,R2,C2;
char G[502][502];
bool VIS[502][502];
bool Solve()
{
	G[R1][C1]='.';
	static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	if(R1==R2&&C1==C2)
	{
		int cnt=0;
		for(int i=0;i<4;i++)
		{
			const int nxtr=R1+d[i][0],nxtc=C1+d[i][1];
			if(G[nxtr][nxtc]=='.')++cnt;
		}
		return cnt>=1;
	}
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)VIS[i][j]=false;
	queue<int>q;
	q.push(R1),q.push(C1),VIS[R1][C1]=true;
	while(!q.empty())
	{
		const int r=q.front();q.pop();
		const int c=q.front();q.pop();
		if(r==R2&&c==C2)
		{
			int cnt=0;
			for(int i=0;i<4;i++)
			{
				const int nxtr=r+d[i][0],nxtc=c+d[i][1];
				if(G[nxtr][nxtc]=='.')++cnt;
			}
			return cnt>=2;
		}
		for(int i=0;i<4;i++)
		{
			const int nxtr=r+d[i][0],nxtc=c+d[i][1];
			if(!VIS[nxtr][nxtc])
			{
				if(G[nxtr][nxtc]=='.')
				{
					VIS[nxtr][nxtc]=true;
					q.push(nxtr),q.push(nxtc);
				}
				else if(nxtr==R2&&nxtc==C2)return true;
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)scanf("%s",G[i]+1);
		for(int i=1;i<=N;i++)G[i][0]=G[i][M+1]='X';
		for(int i=1;i<=M;i++)G[0][i]=G[N+1][i]='X';
		scanf("%d%d%d%d",&R1,&C1,&R2,&C2);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
