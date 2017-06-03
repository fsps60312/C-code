#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int H,W,Y,X;
char GRID[12][12];
bool VIS[12][12][4];
int D[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
queue<int>QX,QY,QD;
void Push(int x,int y,int d)
{
	QX.push(x),QY.push(y),QD.push(d);
}
void Pop(int &x,int &y,int &d)
{
	x=QX.front(),y=QY.front(),d=QD.front();
	QX.pop(),QY.pop(),QD.pop();
}
int main()
{
	scanf("%d%d",&H,&W);
	int d=-1;
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			for(int k=0;k<4;k++)VIS[i][j][k]=false;
			char &v=GRID[i][j];
			scanf("%c",&v);
			bool found=true;
			switch(v)
			{
				case'.':
				case'*':break;
				case'U':d=0,Y=i,X=j;break;
				case'R':d=1,Y=i,X=j;break;
				case'D':d=2,Y=i,X=j;break;
				case'L':d=3,Y=i,X=j;break;
				default:found=false;break;
			}
			if(!found)j--;
		}
	}
	for(int i=1;i<=H;i++)GRID[i][0]=GRID[i][W+1]='*';
	for(int i=1;i<=W;i++)GRID[0][i]=GRID[H+1][i]='*';
	assert(d!=-1);
	Push(X,Y,d);
	while(!QX.empty())
	{
		static int x,y;
		Pop(x,y,d);
		if(VIS[y][x][d])break;
		VIS[y][x][d]=true;
		int tx=x+D[d][0],ty=y+D[d][1];
		if(GRID[ty][tx]=='*')Push(x,y,(d+1)%4);
		else Push(tx,ty,d);
	}
	int ans=0;
	for(int i=1;i<=H;i++)
	{
		for(int j=1;j<=W;j++)
		{
			bool found=false;
			for(int k=0;k<4;k++)if(VIS[i][j][k])found=true;
			if(found)ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
