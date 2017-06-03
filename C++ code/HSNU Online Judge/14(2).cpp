#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
int T,N,M,K,GRID[150][10];
struct State
{
	int v[10];
	State(){}
	State(const State &s){for(int i=0;i<M;i++)v[i]=s.v[i];}
	bool operator<(const State &s)const
	{
		for(int i=0;i<M;i++)if(v[i]!=s.v[i])return v[i]<s.v[i];
		return false;
	}
	bool Move(const int &r,const int &c,const int &w,const int &h,State &t)
	{
		for(int i=0;i<w;i++)if(v[c+i]>0)return false;
		if(r+h>N||c+w>M)return false;
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++)
			{
				if(GRID[r+i][c+j])return false;
			}
		}
		for(int i=0;i<M;i++)t.v[i]=v[i];
		for(int i=0;i<w;i++)t.v[c+i]=h;
		return true;
	}
};
map<State,int>DP[150][10];
int Get(int r,int c,State &s)
{
	if(c==M)
	{
		c=0,r++;
		for(int i=0;i<M;i++)if(s.v[i])s.v[i]--;
	}
	if(r==N)
	{
		for(int i=0;i<M;i++)assert(s.v[i]==0);
		return 0;
	}
	map<State,int>&dp=DP[r][c];
	if(dp.find(s)!=dp.end())return dp[s];
	State t=State(s);
	int ans=Get(r,c+1,t);
	if(s.Move(r,c,2,3,t))ans=max(ans,1+Get(r,c+1,t));
	if(s.Move(r,c,3,2,t))ans=max(ans,1+Get(r,c+1,t));
	return dp[s]=ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&N,&M,&K);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					GRID[i][j]=0;
					DP[i][j].clear();
				}
			}
			for(int i=0;i<K;i++)
			{
				static int x,y;
				scanf("%d%d",&x,&y);
				x--,y--;
				assert(x<N&&y<M);
				GRID[x][y]=1;
			}
			State s;
			for(int i=0;i<M;i++)s.v[i]=0;
			printf("%d\n",Get(0,0,s));
		}
	}
	return 0;
}
