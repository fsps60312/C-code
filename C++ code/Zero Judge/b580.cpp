#include<bits/stdc++.h>
using namespace std;
int T,N,ANS[101][101];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int x,y,cnt=0;x=y=(N+1)/2;
		ANS[x][y]=++cnt;
		for(int i=1;i<=N;i++)
		{
			if(i&1)
			{
				for(int j=0;j<i;j++)ANS[++x][y]=++cnt;
				for(int j=0;j<i;j++)ANS[x][--y]=++cnt;
			}
			else
			{
				for(int j=0;j<i;j++)ANS[--x][y]=++cnt;
				for(int j=0;j<i;j++)ANS[x][++y]=++cnt;
			}
		}
		for(int i=1;i<=N;i++)
		{
			printf("%4d",ANS[1][i]);
			for(int j=2;j<=N;j++)printf(" %4d",ANS[j][i]);
			puts("");
		}
	}
	return 0;
}
