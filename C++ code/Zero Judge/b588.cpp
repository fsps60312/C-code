#include<cstdio>
bool WIN[101][101][101],VISITED[101][101][101];
bool Win(int x[])
{
	bool &win=WIN[x[0]][x[1]][x[2]];
	bool &visited=VISITED[x[0]][x[1]][x[2]];
	if(visited)return win;
	visited=true;
	if(x[0]==0&&x[1]==0&&x[2]==0)return win=false;
	for(int s=1;s<(1<<3);s++)//001,010,011,100,101,110,111
	{
		for(int taken=1;;taken++)
		{
			int next[3]={x[0],x[1],x[2]};
			//i==0,(1<<i)==001
			//i==1,(1<<i)==010
			//i==2,(1<<i)==100
			//s&(1<<i) isn't zero <=> i_th digit is 1
			for(int i=0;i<3;i++)if(s&(1<<i))next[i]-=taken;
			for(int i=0;i<3;i++)if(next[i]<0)goto do_break;
			if(!Win(next))return win=true;
		}
		do_break:;
	}
	return win=false;
}
int main()
{
	for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)for(int k=0;k<=100;k++)VISITED[i][j][k]=false;
	int x,y,z;
	while(scanf("%d",&x)==1&&x)
	{
		scanf("%d%d",&y,&z);
		int begin[3]={x,y,z};
		puts(Win(begin)?"w":"l");
	}
	return 0;
}
