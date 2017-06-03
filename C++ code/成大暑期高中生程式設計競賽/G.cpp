#include<cstdio>
#include<cassert>
//#include<algorithm>
using namespace std;
int G[8][8];
bool In(const int v){return 0<=v&&v<8;}
bool Valid(const int r,const int c)
{
	if(G[r][c]!=0)return false;
	static const int d[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
	for(int i=0;i<8;i++)
	{
		const int dr=d[i][0],dc=d[i][1];
		if(In(r+dr)&&In(c+dc)&&G[r+dr][c+dc]==2)
		{
			for(int y=r+dr,x=c+dc;In(y)&&In(x);y+=dr,x+=dc)
			{
				if(G[y][x]==1)return true;
				if(G[y][x]==0)break;
			}
		}
	}
	return false;
}
int GetInt()
{
	int v;if(scanf("%d",&v)!=1)return -1;
	return v;
}
int main()
{
	freopen("ing.txt","r",stdin);
	for(int v;(v=GetInt())!=-1;)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)G[i][j]=(i==0&&j==0?v:GetInt());
		}
		int ans=0;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)if(Valid(i,j))++ans;//,printf("(%d,%d)\n",i,j);
		}
		printf("%d\n",ans);
	}
	return 0;
}
