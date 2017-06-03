#include<cstdio>
#include<map>
using namespace std;
int T,N,M,K,GRID[150][10],POW[10];
inline int D(const int &s,const int &i){return s/POW[i]%4;}
inline bool Move(const int &s,const int &r,const int &c,const int &w,const int &h,int &t)
{
	if(r+h>N||c+w>M)return false;
	static int i,j;
	for(i=0;i<w;i++)if(D(s,c+i)>0)return false;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			if(GRID[r+i][c+j])return false;
		}
	}
	t=s;
	for(i=0;i<w;i++)t+=POW[c+i]*h;
	return true;
}
map<int,int>DP[150][10];
int TMP[150][10],ANS[150][10];
int Get(int r,int c,int &s)
{
	static int i;
	if(c==M)
	{
		c=0,r++;
		for(i=0;i<M;i++)if(D(s,i))s-=POW[i];
	}
	if(r==N)return 0;
	map<int,int>&dp=DP[r][c];
	if(dp.find(s)!=dp.end())return dp[s];
	int &t=TMP[r][c]=s;
	int &ans=ANS[r][c]=Get(r,c+1,t);
	if(Move(s,r,c,2,3,t))ans=max(ans,1+Get(r,c+1,t));
	if(Move(s,r,c,3,2,t))ans=max(ans,1+Get(r,c+1,t));
	return dp[s]=ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	POW[0]=1;
	for(int i=1;i<10;i++)POW[i]=POW[i-1]*4;
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
				GRID[x][y]=1;
			}
			int s=0;
			printf("%d\n",Get(0,0,s));
		}
	}
	return 0;
}
