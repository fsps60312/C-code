#include<cstdio>
#include<vector>
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
int get_DP(int r,int c)
{
	int &dp=DP[r][c];
	if(dp)return dp;
	vector<Point> fa;
	for(int d=0;d<4;d++)
	{
		int x=r+D[d][0],y=c+D[d][1];
		if(H[x][y]>H[r][c])
		{
			fa.push_back(Point(x,y));
		}
	}
	if(!fa.size())dp=1;
	else
	{
		for(int i=0;i<fa.size();i++)
		{
			getmax(dp,get_DP(fa[i].x,fa[i].y)+1);
		}
	}
	return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d%d",NAME,&R,&C);
		for(int c=1;c<=C;c++)DP[0][c]=DP[R+1][c]=0,H[0][c]=H[R+1][c]=-2147483647;
		for(int r=1;r<=R;r++)
		{
			H[r][0]=H[r][C+1]=-2147483647;
			DP[r][0]=DP[r][C+1]=0;
			for(int c=1;c<=C;c++)
			{
				DP[r][c]=0;
				int &ans=H[r][c];
				scanf("%d",&ans);
			}
		}
		int ans=0;
		for(int r=1;r<=R;r++)
		{
			for(int c=1;c<=C;c++)
			{
				getmax(ans,get_DP(r,c));
			}
		}
		printf("%s: %d\n",NAME,ans);
	}
	return 0;
}
