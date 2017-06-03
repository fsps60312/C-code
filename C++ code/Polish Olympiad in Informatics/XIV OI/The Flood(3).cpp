#include<cstdio>
#include<cassert>
#include<vector> 
#include<utility>
#include<queue>
using namespace std;
const int INF=2147483647;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct Pq
{
	int R,C,H;
	Pq(){}
	Pq(const int _R,const int _C,const int _H):R(_R),C(_C),H(_H){}
};
bool operator<(const Pq &a,const Pq &b){return a.H>b.H;}
int N,M;
int G[1002][1002];
vector<pair<int,int> >LOC[1001];
int VIS[1002][1002],WANT[1002][1002];
bool Bfs(const int start_r,const int start_c,const int start_h)
{
	priority_queue<Pq>pq;
	pq.push(Pq(start_r,start_c,start_h));
//	printf("start(%d,%d,%d)\n",start_r,start_c,start_h);
	bool ans=false;
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.R][p.C]<=p.H)continue;
		VIS[p.R][p.C]=p.H;
		if(VIS[p.R][p.C]==G[p.R][p.C])ans|=WANT[p.R][p.C];
		static int d[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
		for(int i=0;i<4;i++)
		{
			const int nxtr=p.R+d[i][0],nxtc=p.C+d[i][1];
			pq.push(Pq(nxtr,nxtc,max(p.H,G[nxtr][nxtc])));
		}
	}
//	for(int i=1;i<=N;i++)
//	{
//		for(int j=1;j<=M;j++)putchar('0'+VIS[i][j]);
//		puts("");
//	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=1000;i++)LOC[i].clear();
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			scanf("%d",&G[i][j]);
			VIS[i][j]=INF,WANT[i][j]=(G[i][j]>=1);
			if(G[i][j]<0)G[i][j]*=-1;
			LOC[G[i][j]].push_back(make_pair(i,j));
		}
		for(int i=1;i<=N||i<=M;i++)VIS[0][i]=VIS[N+1][i]=VIS[i][0]=VIS[i][M+1]=-INF;
		int ans=0;
		for(int h=0;h<=1000;h++)
		{
			for(int i=0;i<(int)LOC[h].size();i++)
			{
				const pair<int,int>&p=LOC[h][i];
//				puts("a");
				if(VIS[p.first][p.second]>h&&Bfs(p.first,p.second,h))++ans;
//				puts("b");
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
