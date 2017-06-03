#include<cstdio>
int T,N,M,GRID[300][300],DP[300][300];
int min(const int &a,const int &b){return a<b?a:b;}
int min(const int &a,const int &b,const int &c){return min(a,min(b,c));}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)scanf("%d",&GRID[i][j]);
		}
		for(int cnt=0;cnt<=N-1+M-1;cnt++)
		{
			for(int i=0;i<=cnt;i++)
			{
				int y=i,x=M-1-(cnt-i);
				if(y<0||y>=N||x<0||x>=M)continue;
				if(y==0||x==M-1)DP[y][x]=(GRID[y][x]=='O'?0:1);
				else DP[y][x]=min(DP[y-1][x])
			}
		}
	}
	return 0;
}
