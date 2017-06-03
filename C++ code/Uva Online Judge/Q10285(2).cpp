#include<cstdio>
#include<queue>
using namespace std;
int T,R,C,H[102][102],DP[102][102];
char NAME[1000000];
struct Point
{
	int x,y;
	Point(int _x,int _y):x(_x),y(_y){}
};
const int D[4][2]={0,-1,1,0,0,1,-1,0};
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d%d",NAME,&R,&C);
		for(int c=1;c<=C;c++)DP[0][c]=DP[R+1][c]=0;
		queue<Point> q;
		for(int r=1;r<=R;r++)
		{
			DP[r][0]=DP[r][C+1]=0;
			for(int c=1;c<=C;c++)
			{
				DP[r][c]=0;
				int &ans=H[r][c];
				scanf("%d",&ans);
				q.push(Point(r,c));
			}
		}
		int ans=0;
		while(!q.empty())
		{
			Point p=q.front();q.pop();
			if(DP[p.x][p.y])continue;
			bool illegal=true,istop=true;
			for(int d=0;d<4;d++)
			{
				int x=p.x+D[d][0],y=p.y+D[d][1];
				if(H[x][y]>H[p.x][p.y])
				{
					istop=false;
					if(!DP[x][y])
					{
						illegal=false;
						break;
					}
				}
			}
			if(!illegal)continue;
			if(istop)DP[p.x][p.y]=1;
			for(int d=0;d<4;d++)
			{
				int x=p.x+D[d][0],y=p.y+D[d][1];
				if(H[x][y]<H[p.x][p.y])
					q.push(Point(x,y));
				else
					getmax(DP[p.x][p.y],DP[x][y]+1);
			}
			getmax(ans,DP[p.x][p.y]);
		}
		printf("%s: %d\n",NAME,ans);
	}
	return 0;
}
