#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Spot
{
	int i,j;
	Spot(){}
	Spot(const int _i,const int _j):i(_i),j(_j){}
};
int N,M,A,B;
int GRID[30][30];
bool INQ[30][30];
void Move(queue<Spot>&q,const int i,const int j)
{
	if(!INQ[i][j])q.push(Spot(i,j)),INQ[i][j]=true;
}
int Dfs(const int i,const int j,const int color)
{
	assert(GRID[i][j]==0&&!INQ[i][j]&&(color==-1||color==1));
	GRID[i][j]=color,INQ[i][j]=true;
	int ans=0;
	int d[4][2]={{-A,-B},{-A,B},{A,-B},{A,B}};
	for(int t=0;t<4;t++)
	{
		const int nxti=i+d[t][0],nxtj=j+d[t][1];
		if(nxti<0||nxtj<0||nxti>=N||nxtj>=M)continue;
		if(GRID[nxti][nxtj]==0)ans+=1+Dfs(nxti,nxtj,-color);
		else if(GRID[nxti][nxtj]==-color)ans++;
	}
	return ans;
}
void ClearDfs(bool reset)
{
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)if(INQ[i][j])
	{
		if(reset)GRID[i][j]=0;
		INQ[i][j]=false;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(4,"%d%d%d%d",&N,&M,&A,&B);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf(1,"%d",&GRID[i][j]);
		queue<Spot>q;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)q.push(Spot(i,j)),INQ[i][j]=true;
		while(!q.empty())
		{
			const Spot p=q.front();q.pop();
			INQ[p.i][p.j]=false;
			if(GRID[p.i][p.j]!=0)continue;
			int *cnt=new int[3]{0,0,0};
			if(p.i-A>=0)
			{
				if(p.j-B>=0)cnt[GRID[p.i-A][p.j-B]+1]++;
				if(p.j+B<M)cnt[GRID[p.i-A][p.j+B]+1]++;
			}
			if(p.i+A<N)
			{
				if(p.j-B>=0)cnt[GRID[p.i+A][p.j-B]+1]++;
				if(p.j+B<M)cnt[GRID[p.i+A][p.j+B]+1]++;
			}
			const int sum=cnt[0]+cnt[1]+cnt[2];
			if(cnt[0]&&cnt[0]*2>=sum)GRID[p.i][p.j]=1;
			else if(cnt[2]&&cnt[2]*2>=sum)GRID[p.i][p.j]=-1;
			else goto do_continue;
			if(p.i-A>=0)
			{
				if(p.j-B>=0)Move(q,p.i-A,p.j-B);
				if(p.j+B<M)Move(q,p.i-A,p.j+B);
			}
			if(p.i+A<N)
			{
				if(p.j-B>=0)Move(q,p.i+A,p.j-B);
				if(p.j+B<M)Move(q,p.i+A,p.j+B);
			}
			do_continue:;
			delete[]cnt;
		}
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)assert(!INQ[i][j]);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)if(GRID[i][j]==0)
		{
			const int a=Dfs(i,j,-1);
			ClearDfs(true);
			const int b=Dfs(i,j,1);
			if(a>b)ClearDfs(true),assert(a==Dfs(i,j,-1));
			ClearDfs(false);
		}
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)assert(GRID[i][j]==-1||GRID[i][j]==1);
		int ans=0;
		for(int i=0;i+A<N;i++)for(int j=0;j<M;j++)
		{
			if(j-B>=0&&GRID[i][j]!=GRID[i+A][j-B])ans++;
			if(j+B<M&&GRID[i][j]!=GRID[i+A][j+B])ans++;
		}
		printf("%d\n",ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
