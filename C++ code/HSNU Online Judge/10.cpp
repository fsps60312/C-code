#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int N,W[2],H[2],X[2],Y[2];
int G[2][500][500];
bool VIS[2][500][500];
struct Pq
{
	int k,x,y,v;
	Pq(){}
	Pq(int k,int x,int y,int v):k(k),x(x),y(y),v(v){}
	bool operator<(const Pq &p)const{return v>p.v;}
};
int Solve()
{
	priority_queue<Pq>pq;
	for(int i=0;i<2;i++)pq.push(Pq(i,X[i],Y[i],G[i][X[i]][Y[i]]));
	int cnt=0,v[2]={0,0};
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		bool &vis=VIS[p.k][p.x][p.y];
		if(vis)continue;vis=true;
		cnt++;
		v[p.k]=p.v;
		if(cnt==N)return max(v[0],v[1]);
		if(p.x)pq.push(Pq(p.k,p.x-1,p.y,v[p.k]+G[p.k][p.x-1][p.y]));
		if(p.y)pq.push(Pq(p.k,p.x,p.y-1,v[p.k]+G[p.k][p.x][p.y-1]));
		if(p.x+1<W[p.k])pq.push(Pq(p.k,p.x+1,p.y,v[p.k]+G[p.k][p.x+1][p.y]));
		if(p.y+1<H[p.k])pq.push(Pq(p.k,p.x,p.y+1,v[p.k]+G[p.k][p.x][p.y+1]));
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
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
					VIS[k][i][j]=false;
					scanf("%d",&G[k][j][i]);
				}
			}
		}
		printf("%d\n",Solve());
	}
	return 0;
} 
