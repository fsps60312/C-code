#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
bool AtRange(const int v,const int l,const int r){return l<=v&&v<=r;}
int N,S;
char GRID[800*800+1];
int BEE[800*800],START,END;
bool Solve(const int time)
{
//	printf("%d to %d\n",START,END);
	assert(AtRange(START,0,N*N-1)&&AtRange(END,0,N*N-1));
	static int dist[800*800];
	for(int i=0;i<N*N;i++)dist[i]=INF;
	queue<int>q;
	q.push(START),dist[START]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		assert(dist[u]!=INF);
		const int row=u/N,col=u%N;
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			const int nxtrow=row+d[i][0],nxtcol=col+d[i][1],nxtu=nxtrow*N+nxtcol;
			if(AtRange(nxtrow,0,N-1)&&AtRange(nxtcol,0,N-1))
			{
				if(nxtu==END)
				{
//					printf("time=%d\n",time);
//					for(int i=0;i<N;i++)
//					{
//						for(int j=0;j<N;j++)
//						{
//							int v=dist[i*N+j];
//							printf(" %2d",v==INF?-1:v);
//						}
//						puts("");
//					}puts("");
					return true;
				}
				if(GRID[nxtu]!='T'&&time+(dist[u]+1)/S<BEE[nxtu])
				{
					assert(GRID[nxtu]=='G');
					if(dist[nxtu]==INF)dist[nxtu]=dist[u]+1,q.push(nxtu);
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&S)==2)
	{
		for(int i=0;i<N;i++)assert(scanf("%s",GRID+i*N)==1);
		for(int i=0;i<N*N;i++)BEE[i]=INF;
		START=-1,END=-1;
		queue<int>q;
		for(int i=0;i<N*N;i++)
		{
			char &grid=GRID[i];
			switch(grid)
			{
				case'T':case'G':break;
				case'M':START=i,grid='G';break;
				case'D':END=i,grid='T';break;
				case'H':q.push(i),BEE[i]=0,grid='G';break;
				default:assert(0);break;
			}
		}
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			const int row=u/N,col=u%N;
			static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
			for(int i=0;i<4;i++)
			{
				const int nxtrow=row+d[i][0],nxtcol=col+d[i][1],nxtu=nxtrow*N+nxtcol;
				if(AtRange(nxtrow,0,N-1)&&AtRange(nxtcol,0,N-1)&&GRID[nxtu]!='T')
				{
					assert(GRID[nxtu]=='G');
					if(BEE[nxtu]==INF)BEE[nxtu]=BEE[u]+1,q.push(nxtu);
				}
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<N;j++)
//			{
//				int v=BEE[i*N+j];
//				printf(" %2d",v==INF?-1:v);
//			}
//			puts("");
//		}puts("");
		int l=-1,r=(BEE[START]==INF?N*N:BEE[START]-1);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",r);
		break;
	}
	return 0;
}
