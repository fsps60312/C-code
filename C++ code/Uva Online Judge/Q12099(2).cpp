#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=1<<30;
struct Book
{
	int h,w;
}BOOK[70];
int T,N,DP[2][2101][2101],WIDTH;
bool cmp_BOOK(Book a,Book b){return a.h>b.h;}
void getmax(int &a,int b){if(b>a)a=b;}
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
int max(int a,int b,int c){if(b>a)a=b;if(c>a)a=c;return a;}
int max(int a,int b){return a>b?a:b;}
struct Point
{
	int x,y;
};
int get_width(int sum,int w1,int w2){return max(sum-w1-w2,w1,w2);}
int main()
{
	//freopen("in.txt","r",stdin); 
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		WIDTH=0;
		for(int i=0;i<N;i++)
		{
			Book &b=BOOK[i];
			scanf("%d%d",&b.h,&b.w);
			if(i>0)WIDTH+=b.w;
		}
		sort(BOOK,BOOK+N,cmp_BOOK);
//		for(int i=0;i<N;i++)printf("%d %d\n",BOOK[i].h,BOOK[i].w);
		for(int i=0;i<=WIDTH;i++)
		{
			for(int j=0;j<=WIDTH;j++)
			{
				DP[0][i][j]=DP[1][i][j]=INF;
			}
		}
		queue<Point> q[2];
		DP[0][0][0]=BOOK[0].h;
		q[0].push((Point){0,0});
		int noww=BOOK[0].w;
		int ans=INF;
		for(int ti=1;ti<N;ti++)
		{
			int i=ti&1;
			noww+=BOOK[ti].w;
			while(!q[i^1].empty())
			{
				Point p=q[i^1].front();q[i^1].pop();
				int dp=DP[i^1][p.x][p.y];
				DP[i^1][p.x][p.y]=INF;
				if(DP[i][p.x][p.y]>dp)//put to floor 1
				{
					//printf("%d : %d %d %d %d %d\n",ti,noww-j-k,j,k,DP[i][j][k],ans);
					int &td=DP[i][p.x][p.y];
					if(td==INF)q[i].push((Point){p.x,p.y});
					td=dp;
					if(ti==N-1&&p.x&&p.y)getmin(ans,get_width(noww,p.x,p.y)*td);
				}
				if(DP[i][p.x+BOOK[ti].w][p.y]>dp+(p.x?0:BOOK[ti].h))//put to floor 2
				{
					int &td=DP[i][p.x+BOOK[ti].w][p.y];
					if(td==INF)q[i].push((Point){p.x+BOOK[ti].w,p.y});
					td=dp+(p.x?0:BOOK[ti].h);
					//printf("%d : %d %d %d %d %d\n",ti,noww-(j+BOOK[ti].w)-k,j+BOOK[ti].w,k,DP[i][j+BOOK[ti].w][k],ans);
					if(ti==N-1&&p.y)getmin(ans,get_width(noww,p.x+BOOK[ti].w,p.y)*td);
				}
				if(p.x==0&&p.y==0)continue;
				if(DP[i][p.x][p.y+BOOK[ti].w]>dp+(p.y?0:BOOK[ti].h))//put to floor 3
				{
					int &td=DP[i][p.x][p.y+BOOK[ti].w];
					if(td==INF)q[i].push((Point){p.x,p.y+BOOK[ti].w});
					td=dp+(p.y?0:BOOK[ti].h);
					//printf("%d : %d %d %d %d %d\n",ti,noww-j-(k+BOOK[ti].w),j,k+BOOK[ti].w,DP[i][j][k+BOOK[ti].w],ans);
					if(ti==N-1)getmin(ans,get_width(noww,p.x,p.y+BOOK[ti].w)*td);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
