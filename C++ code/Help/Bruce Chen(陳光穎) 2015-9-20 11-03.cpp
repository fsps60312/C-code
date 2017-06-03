#include<cstdio>
#include<map>
using namespace std;
int N;
struct State
{
	int s1,s2,grid[4][4];
	State():s1(0),s2(0){for(int i=0;i<N;i++)for(int j=0;j<N;j++)grid[i][j]=0;}
	bool operator<(const State &s)const
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		if(grid[i][j]!=s.grid[i][j])return grid[i][j]<s.grid[i][j];
		return false;
	}
	int &Score(int player){return player==1?s1:s2;}
	bool IsChess(int x,int y,int player)
	{
		if(x<0||y<0||x>=N||y>=N)return false;
		return grid[x][y]==player;
	}
	int Sq(int a){return a*a;}
	void GainScore(int x,int y)
	{
		int player=grid[x][y];
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			if(grid[i][j]!=player||(i==x&&j==y))continue;
			int dx=i-x,dy=j-y;
			if(IsChess(i-dy,j+dx,player)&&IsChess(x-dy,y+dx,player))
				Score(player)+=Sq(dx+dy+1);
		}
	}
};
map<State,int>DP;
int dfs(State &s,int player)
{
	if(DP.find(s)!=DP.end())return DP[s];
	int ans=3-player;
	int cnt=0;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		if(s.grid[i][j])continue;
		cnt++;
		State t=s;
		t.grid[i][j]=player;
		t.GainScore(i,j);
		int s1=t.Score(player),s2=t.Score(3-player);
		if(s1>=150&&s1-s2>=15){ans=player;break;}
		int dp=dfs(t,3-player);
		if(dp==player){ans=player;break;}
		else if(dp==0)ans=0;
	}
	if(!cnt)
	{
		int s1=s.Score(player),s2=s.Score(3-player);
		if(s1>=150&&s1-s2>=15)ans=player;
		else ans=0;
	}
//	printf("%s\n",ans==0?"tie":ans==1?"win":"lose");
//	for(int i=0;i<N;i++)
//	{
//		for(int j=0;j<N;j++)printf("%d",s.grid[i][j]);
//		puts("");
//	}
	return DP[s]=ans;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		DP.clear();
		State s=State();
		int ans=dfs(s,1);
		printf("%s\n",ans==0?"TIE":ans==1?"WIN":"LOSE");
	}
	return 0;
}
