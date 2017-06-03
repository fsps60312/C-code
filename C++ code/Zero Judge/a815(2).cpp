#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M,DP[90000];
char GRID[300][300];
bool INQ[90000];
int min(const int &a,const int &b){return a<b?a:b;}
int min(const int &a,const int &b,const int &c){return min(a,min(b,c));}
void Push(queue<int>&q,const int &v)
{
	if(INQ[v])return;
	q.push(v);
	INQ[v]=true;
}
void Pop(queue<int>&q,int &v){v=q.front();q.pop();INQ[v]=false;}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&T)==1);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			char &v=GRID[i][j];
			do
			{
				scanf("%c",&v);
			}while(v!='.'&&v!='O');
		}
		for(int i=0;i<N*M;i++)DP[i]=INF,INQ[i]=false;
		queue<int>q;
		for(int i=1;i<M;i++)
		{
			int u=0*M+i;
			Push(q,u);
			DP[u]=GRID[0][i]=='O'?0:1;
		}
		for(int i=1;i<N-1;i++)
		{
			int u=i*M+(M-1);
			Push(q,u);
			DP[u]=GRID[i][M-1]=='O'?0:1;
		}
		while(!q.empty())
		{
			static int u;Pop(q,u);
			static int d[6][2]={{1,0},{-1,0},{0,1},{0,-1},{-1,1},{1,-1}};
			for(int i=0,x,y;i<6;i++)
			{
				y=u/M+d[i][0],x=u%M+d[i][1];
				if(y<0||x<0||y>=N||x>=M)continue;
				if((x==0&&y==0)||(x==M-1&&y==N-1))continue;
				int cost=(GRID[y][x]=='O'?0:1);
				if(DP[u]+cost<DP[y*M+x])
				{
					DP[y*M+x]=DP[u]+cost;
					Push(q,y*M+x);
				}
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<M;j++)printf(" %d",DP[i*M+j]);
//			puts("");
//		}
		int ans=INF;
		for(int i=1;i<N;i++)ans=min(ans,DP[i*M+0]);
		for(int i=1;i<M-1;i++)ans=min(ans,DP[(N-1)*M+i]);
		printf("%d\n",ans);
	}
	return 0;
}
