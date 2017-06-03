#include<cstdio>
#include<queue>
#include<cassert>
#include<deque>
using namespace std;
const int INF=2147483647;
int T,N,M,DP[90000];
char GRID[300][300];
bool VIS[90000];
int min(const int &a,const int &b){return a<b?a:b;}
int min(const int &a,const int &b,const int &c){return min(a,min(b,c));}
void Push(queue<int>&q,const int &u,const int &v)
{
	if(VIS[u])return;
	VIS[u]=true;
	DP[u]=v;
	q.push(u);
}
void FillHoney(queue<int>&rq,const int &s,const int &v)
{
	queue<int>q;
	Push(q,s,v);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		static int d[6][2]={{1,0},{-1,0},{0,1},{0,-1},{-1,1},{1,-1}};
		for(int i=0,x,y;i<6;i++)
		{
			y=u/M+d[i][0],x=u%M+d[i][1];
			if(y<0||x<0||y>=N||x>=M)continue;
			if((x==0&&y==0)||(x==M-1&&y==N-1))continue;
			if(GRID[y][x]!='O')Push(rq,y*M+x,v+1);
			else Push(q,y*M+x,v);
		}
	}
}
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
		for(int i=0;i<N*M;i++)DP[i]=INF,VIS[i]=false;
		queue<int>q;
		for(int i=1;i<M;i++)
		{
			if(GRID[0][i]=='.')continue;
			Push(q,0*M+i,0);
		}
		for(int i=1;i<N-1;i++)
		{
			if(GRID[i][M-1]=='.')continue;
			Push(q,i*M+(M-1),0);
		}
		if(q.empty())
		{
			for(int i=1;i<M;i++)Push(q,0*M+i,1);
			for(int i=1;i<N-1;i++)Push(q,i*M+(M-1),1);
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			static int d[6][2]={{1,0},{-1,0},{0,1},{0,-1},{-1,1},{1,-1}};
			for(int i=0,x,y;i<6;i++)
			{
				y=u/M+d[i][0],x=u%M+d[i][1];
				if(y<0||x<0||y>=N||x>=M)continue;
				if((x==0&&y==0)||(x==M-1&&y==N-1))continue;
				if(GRID[y][x]=='O')FillHoney(q,y*M+x,DP[u]);
				else Push(q,y*M+x,DP[u]+1);
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
