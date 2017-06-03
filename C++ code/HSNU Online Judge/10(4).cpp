#include<cstdio>
#include<queue>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,W[2],H[2],X[2],Y[2];
int G[2][500][500];
bool VIS[2][500][500];
struct Pq
{
	int k,x,y,v;
	Pq(){}
	Pq(int k,int x,int y):k(k),x(x),y(y),v(G[k][x][y]){}
	bool operator<(const Pq &p)const{return v>p.v;}
};
int CNT[2][250001];
int Build()
{
	priority_queue<Pq>pq;
	for(int i=0;i<2;i++)pq.push(Pq(i,X[i],Y[i]));
	int cnt[2]={0,0},ans[2]={0,0};
	CNT[0][0]=CNT[1][0]=0;
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		bool &vis=VIS[p.k][p.x][p.y];
		if(vis)continue;vis=true;
		ans[p.k]=max(ans[p.k],p.v);
		CNT[p.k][++cnt[p.k]]=ans[p.k];
		if(p.x)pq.push(Pq(p.k,p.x-1,p.y));
		if(p.y)pq.push(Pq(p.k,p.x,p.y-1));
		if(p.x+1<W[p.k])pq.push(Pq(p.k,p.x+1,p.y));
		if(p.y+1<H[p.k])pq.push(Pq(p.k,p.x,p.y+1));
	}
//	for(int i=0;i<cnt[0];i++)printf("%d:%d\n",i,CNT[0][i]);
//	for(int i=0;i<cnt[1];i++)printf("%d:%d\n",i,CNT[1][i]);
	int rans=INF;
	for(int i=0;i<=cnt[0];i++)
	{
		if(N-i>cnt[1])continue;
		else if(N-i<0)break;
		rans=min(rans,CNT[0][i]+CNT[1][N-i]);
	}
	return rans;
}
int main()
{
//	printf("%d\n",100000000+100000000);
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int k=0;k<2;k++)
		{
			scanf("%d%d%d%d",&W[k],&H[k],&X[k],&Y[k]);
			X[k]--,Y[k]--;
			for(int i=0;i<H[k];i++)
			{
				for(int j=0;j<W[k];j++)
				{
					VIS[k][j][i]=false;
					scanf("%d",&G[k][j][i]);
				}
			}
		}
		printf("%d\n",Build());
	}
	return 0;
} 
