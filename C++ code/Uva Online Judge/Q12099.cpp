#include<cstdio>
#include<algorithm>
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
				DP[0][i][j]=INF;
			}
		}
		DP[0][0][0]=BOOK[0].h;
		int noww=BOOK[0].w;
		int ans=INF;
		for(int ti=1;ti<N;ti++)
		{
			int i=ti&1;
			for(int j=0;j<=WIDTH;j++)
			{
				for(int k=0;k<=WIDTH;k++)
				{
					DP[i][j][k]=INF;
				}
			}
			noww+=BOOK[ti].w;
			for(int j=0;j<=WIDTH;j++)
			{
				for(int k=0;k<=WIDTH;k++)
				{
					if(j==0&&k>0)break;
					if(DP[i^1][j][k]==INF)continue;
					if(getmin(DP[i][j][k],DP[i^1][j][k]))//put to floor 1
					{
						//printf("%d : %d %d %d %d %d\n",ti,noww-j-k,j,k,DP[i][j][k],ans);
						if(ti==N-1&&j&&k)getmin(ans,max(noww-j-k,j,k)*DP[i][j][k]);
					}
					if(getmin(DP[i][j+BOOK[ti].w][k],DP[i^1][j][k]+(j?0:BOOK[ti].h)))//put to floor 2
					{
						//printf("%d : %d %d %d %d %d\n",ti,noww-(j+BOOK[ti].w)-k,j+BOOK[ti].w,k,DP[i][j+BOOK[ti].w][k],ans);
						if(ti==N-1&&k)getmin(ans,max(noww-(j+BOOK[ti].w)-k,j+BOOK[ti].w,k)*DP[i][j+BOOK[ti].w][k]);
					}
					if(k==0&&j==0)continue;
					if(getmin(DP[i][j][k+BOOK[ti].w],DP[i^1][j][k]+(k?0:BOOK[ti].h)))//put to floor 3
					{
						//printf("%d : %d %d %d %d %d\n",ti,noww-j-(k+BOOK[ti].w),j,k+BOOK[ti].w,DP[i][j][k+BOOK[ti].w],ans);
						if(ti==N-1)getmin(ans,max(noww-j-(k+BOOK[ti].w),j,k+BOOK[ti].w)*DP[i][j][k+BOOK[ti].w]);
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
