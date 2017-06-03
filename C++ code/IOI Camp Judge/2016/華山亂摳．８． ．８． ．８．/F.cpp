#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M,ANS[100001];
vector<vector<int> >GRID,SUM;
int GetSUM(const int i1,const int i2,const int j1,const int j2)
{
	assert(i1>0&&j1>0&&i2<=N+2&&j2<=M+2);
	return SUM[i2][j2]-SUM[i2][j1-1]-SUM[i1-1][j2]+SUM[i1-1][j1-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		GRID.resize(N+3),SUM.resize(N+3);
		for(auto &v:GRID)v.resize(M+3);
		for(auto &v:SUM)v.resize(M+3);
		for(int i=2;i<=N+1;i++)
		{
			static char s[100003];scanf("%s",s+2);
			for(int j=2;j<=M+1;j++)GRID[i][j]=(s[j]=='#'?1:0);
		}
		for(int i=0;i<N+3;i++)GRID[i][1]=GRID[i][M+2]=1;
		for(int i=0;i<M+3;i++)GRID[1][i]=GRID[N+2][i]=1;
		for(int i=1;i<=N+2;i++)for(int j=1;j<=M+2;j++)SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+GRID[i][j];
		for(int i=0;i<=min(N,M);i++)ANS[i]=0;
		for(int i=2;i<=N+1;i++)
		{
			for(int j=2,len=0;j<=M+1;j++)
			{
				if(len)len--;
				while(GetSUM(i,i+len,j,j+len)==0)len++;
				ANS[len]++;
			}
		}
		for(int i=min(N,M)-1;i>=0;i--)ANS[i]+=ANS[i+1];
		for(int i=1;i<=min(N,M);i++)
		{
			if(i>1)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
