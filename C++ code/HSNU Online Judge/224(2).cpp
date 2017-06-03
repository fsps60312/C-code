#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
struct Spot
{
	int i,j;
	Spot(){}
	Spot(const int _i,const int _j):i(_i),j(_j){}
};
int N,M,A,B;
int GRID[30][30];
int CNT[30][30][3];
bool INQ[30][30];
void Move(queue<Spot>&q,const int i,const int j,const int from,const int to)
{
	CNT[i][j][from]--,CNT[i][j][to]++;
	if(!INQ[i][j])q.push(Spot(i,j)),INQ[i][j]=true;
}
int Dfs(const int i,const int j,const int color)
{
	assert(GRID[i][j]==1&&!INQ[i][j]&&(color==0||color==2));
	GRID[i][j]=color,INQ[i][j]=true;
	int ans=0;
	int d[4][2]={{-A,-B},{-A,B},{A,-B},{A,B}};
	for(int i=0;i<4;i++)
	{
		const int nxti=i+d[i][0],nxtj=j+d[i][1];
		if(nxti<0||nxtj<0||nxti>=N||nxtj>=M)continue;
		if(GRID[nxti][nxtj]==1)ans+=1+Dfs(nxti,nxtj,2-color);
		else if(GRID[nxti][nxtj]==2-color)ans++;
	}
	return ans;
}
void ClearDfs(bool reset)
{
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)if(INQ[i][j])
	{
		if(reset)GRID[i][j]=1;
		INQ[i][j]=false;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d%d",&N,&M,&A,&B);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)for(int k=0;k<3;k++)CNT[i][j][k]=0;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			int &v=GRID[i][j];
			scanf("%d",&v),v++;
			if(i-A>=0)
			{
				if(j-B>=0)CNT[i-A][j-B][v]++;
				if(j+B<M)CNT[i-A][j+B][v]++;
			}
			if(i+A<N)
			{
				if(j-B>=0)CNT[i+A][j-B][v]++;
				if(j+B<M)CNT[i+A][j+B][v]++;
			}
		}
		queue<Spot>q;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)q.push(Spot(i,j)),INQ[i][j]=true;
		while(!q.empty())
		{
			const Spot p=q.front();q.pop();
			INQ[p.i][p.j]=false;
			if(GRID[p.i][p.j]!=1)continue;
			const int *cnt=CNT[p.i][p.j];
			const int sum=cnt[0]+cnt[1]+cnt[2];
			if(cnt[0]*2>=sum)GRID[p.i][p.j]=2;
			else if(cnt[2]*2>=sum)GRID[p.i][p.j]=0;
			else continue;
			const int nowv=GRID[p.i][p.j];
			if(p.i-A>=0)
			{
				if(p.j-B>=0)Move(q,p.i-A,p.j-B,1,nowv);
				if(p.j+B<M)Move(q,p.i-A,p.j+B,1,nowv);
			}
			if(p.i+A<N)
			{
				if(p.j-B>=0)Move(q,p.i+A,p.j-B,1,nowv);
				if(p.j+B<M)Move(q,p.i+A,p.j+B,1,nowv);
			}
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)printf("%d ",GRID[i][j]);
			puts("");
		}
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)assert(!INQ[i][j]);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)if(GRID[i][j]==1)
		{
			const int a=Dfs(i,j,0);
			ClearDfs(true);
			const int b=Dfs(i,j,2);
			if(a>b)ClearDfs(true),Dfs(i,j,0);
			ClearDfs(false);
		}
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)assert(GRID[i][j]==0||GRID[i][j]==2);
		int ans=0;
		for(int i=0;i+A<N;i++)for(int j=0;j<M;j++)
		{
			if(j-B>=0&&GRID[i][j]!=GRID[i+A][j-B])ans++;
			if(j+B<M&&GRID[i][j]!=GRID[i+A][j+B])ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
2 5 1 4
0 -1 -1 -1 0
0 0 1 1 0
*/
