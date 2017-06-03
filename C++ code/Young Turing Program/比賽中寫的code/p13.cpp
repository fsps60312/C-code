#include<cstdio>
#include<cassert>
using namespace std;
int N,M;
char G[5000][5001];
bool Check(int i,int j)
{
	if(i<0||j<0||i>=N||j>=M)return false;
	return G[i][j]=='*';
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		if(N==0&&M==0)break;
		for(int i=0;i<N;i++)scanf("%s",G[i]);
		static int kase=0;
		if(kase)puts("");
		printf("#%d:\n",++kase);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(G[i][j]=='*')putchar('*');
				else
				{
					int cnt=0;
					static int d[8][2]={{0,-1},{0,1},{-1,0},{1,0},{1,-1},{1,1},{-1,-1},{-1,1}};
					for(int k=0;k<8;k++)if(Check(i+d[k][0],j+d[k][1]))++cnt;
					putchar('0'+cnt);
				}
			}
			puts("");
		}
	}
	return 0;
}
