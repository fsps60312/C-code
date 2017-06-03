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
inline bool cmp_BOOK(Book a,Book b){return a.h>b.h;}
inline void getmax(int &a,int b){if(b>a)a=b;}
inline bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
inline int max(int a,int b,int c){if(b>a)a=b;if(c>a)a=c;return a;}
inline int max(int a,int b){return a>b?a:b;}
struct Point
{
	int x,y;
};
inline int get_width(int sum,int w1,int w2){return max(sum-w1-w2,w1,w2);}
inline int abs(int a){return a>=0?a:-a;}
int main()
{
//	freopen("in.txt","r",stdin); 
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		WIDTH=0;
		int maxw=0;
		for(int i=0;i<N;i++)
		{
			Book &b=BOOK[i];
			scanf("%d%d",&b.h,&b.w);
			if(b.w>maxw)maxw=b.w;
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
				int w1=p.x,w2=p.y;
				if(DP[i][w1][w2]>dp)//put to floor 1
				{
					//printf("%d : %d %d %d %d %d\n",ti,noww-j-k,j,k,DP[i][j][k],ans);
					int &td=DP[i][w1][w2];
					if(td==INF)q[i].push((Point){w1,w2});
					td=dp;
					if(ti==N-1&&w1&&w2)getmin(ans,get_width(noww,w1,w2)*td);
				}
				w1=p.x+BOOK[ti].w;
				if(!(w1>noww-w1-w2+maxw)&&DP[i][w1][w2]>dp+(p.x?0:BOOK[ti].h))//put to floor 2
				{
					int &td=DP[i][w1][w2];
					if(td==INF)q[i].push((Point){w1,w2});
					td=dp+(p.x?0:BOOK[ti].h);
					//printf("%d : %d %d %d %d %d\n",ti,noww-(j+BOOK[ti].w)-k,j+BOOK[ti].w,k,DP[i][j+BOOK[ti].w][k],ans);
					if(ti==N-1&&p.y)getmin(ans,get_width(noww,w1,w2)*td);
				}
				if(p.x==0&&p.y==0)continue;
				w1=p.x,w2=p.y+BOOK[ti].w;
				if(!(w2>w1+maxw)&&DP[i][w1][w2]>dp+(p.y?0:BOOK[ti].h))//put to floor 3
				{
					int &td=DP[i][w1][w2];
					if(td==INF)q[i].push((Point){w1,w2});
					td=dp+(p.y?0:BOOK[ti].h);
					//printf("%d : %d %d %d %d %d\n",ti,noww-j-(k+BOOK[ti].w),j,k+BOOK[ti].w,DP[i][j][k+BOOK[ti].w],ans);
					if(ti==N-1)getmin(ans,get_width(noww,w1,w2)*td);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
