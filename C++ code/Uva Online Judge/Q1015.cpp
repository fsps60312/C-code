#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(a<b)a=b;}
char GRID[21][4*20+3+2];
char ANSA[21][42],ANSO[21][42];
int W,H;
bool Solve()
{
	bool changed=false;
	static bool vis[21][41];
	for(int y=1;y<=H;y++)for(int x=1;x<W*2+1;x+=2)vis[y][x]=false;
	for(int h=1;h<=H;h++)
	{
		for(int w=1;w<W*2+1;w+=2)
		{
			assert(ANSA[h][w]==' '||ANSA[h][w]=='_');
			int up=h,down=h,left=w,right=w;
			queue<int>q;
			q.push(h),q.push(w);
			while(!q.empty())
			{
				const int y=q.front();q.pop();
				const int x=q.front();q.pop();
				if(vis[y][x])continue;
				vis[y][x]=true;
				getmin(down,y),getmax(up,y);
				getmin(left,x),getmax(right,x);
				if(y-1>=1&&ANSA[y-1][x]!='_')q.push(y-1),q.push(x);
				if(y+1<=H&&ANSA[y][x]!='_')q.push(y+1),q.push(x);
				if(x-2>=0&&ANSA[y][x-1]!='|')q.push(y),q.push(x-2);
				if(x+2<W*2+1&&ANSA[y][x+1]!='|')q.push(y),q.push(x+2);
			}
			for(int y=down;y<up;y++)for(int x=left;x<=right;x++)if(ANSA[y][x]!=' ')
			{
				changed=true;
				ANSA[y][x]=' ';
			}
			for(int x=left;x<=right;x++)if(ANSA[up][x]=='|')
			{
				changed=true;
				ANSA[up][x]=' ';
			}
		}
	}
	return changed;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(true)
	{
		fgets(GRID[0],INF,stdin);
		assert(sscanf(GRID[0],"%d%d",&W,&H)==2);
		if(W==0&&H==0)break;
		for(int i=0;i<H+1;i++)fgets(GRID[i],INF,stdin);
		for(int i=0;i<H+1;i++)ANSA[i][W*2+1]=ANSO[i][W*2+1]='\0';
		for(int i=0;i<H+1;i++)for(int j=0;j<W*2+1;j++)
		{
			if(GRID[i][j]!=' '&&GRID[i][W*2+2+j]!=' ')ANSA[i][j]=GRID[i][j];
			else ANSA[i][j]=' ';
			if(GRID[i][j]!=' '||GRID[i][W*2+2+j]!=' ')ANSO[i][j]=(GRID[i][j]!=' '?GRID[i][j]:GRID[i][W*2+2+j]);
			else ANSO[i][j]=' '; 
		}
		while(Solve());
		static int kase=0;
		printf("Case %d:\n",++kase);
		for(int i=0;i<H+1;i++)printf("%s %s\n",ANSO[i],ANSA[i]);
		puts("");
	}
	return 0;
}
