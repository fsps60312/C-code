#include<cstdio>
#include<cstdlib>
#include<queue>
const int INF=2147483647;
using namespace std;
int R,C,SR,SC,ER,EC,MAP[102][102][4],BEST[102][102][4][2];
int D[4][2]={-1,0,0,1,1,0,0,-1};
struct Trip
{
	int r,c,d,l,acced;
	bool operator<(Trip a)const{return l>a.l;}
};
int solve()
{
	for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)for(int d=0;d<4;d++)BEST[r][c][d][0]=BEST[r][c][d][1]=INF;
	priority_queue<Trip> pq;
	for(int d=0;d<4;d++)pq.push((Trip){SR,SC,d,0,2});
	int ans=2147483647;
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		if(t.r==ER&&t.c==EC&&t.l+(t.acced==1?MAP[t.r][t.c][(t.d+2)%4]:0)<ans)
			ans=t.l+(t.acced==1?MAP[t.r][t.c][(t.d+2)%4]:0);
		if(t.l>=BEST[t.r][t.c][t.d][t.acced-1])continue;
		BEST[t.r][t.c][t.d][t.acced-1]=t.l;
		if(!MAP[t.r][t.c][t.d])continue;
		//printf("  in(%d,%d,%d,%d,%d)\n",t.r,t.c,t.d,t.prel,t.l);
		int r,c,d,l;
		r=t.r+D[t.d][0];
		c=t.c+D[t.d][1];
		d=t.d;
		l=t.l+MAP[t.r][t.c][t.d]*t.acced;
		//printf("push(%d,%d,%d,%d,%d)\n",r,c,d,prel,l);
		pq.push((Trip){r,c,d,l,1});
		if(t.acced==1)l+=MAP[t.r][t.c][t.d];
		for(d=0;d<4;d++)
		{
			if(d==t.d)continue;
			//printf("push(%d,%d,%d,%d,%d)\n",r,c,d,prel,l);
			pq.push((Trip){r,c,d,l,2});
		}
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d%d%d%d%d",&R,&C,&SR,&SC,&ER,&EC)==6&&(R||C||SR||SC||ER||EC))
	{
		for(int c=1;c<=C;c++)MAP[1][c][0]=MAP[R][c][2]=0;
		for(int r=1;;r++)
		{
			MAP[r][1][3]=MAP[r][C][1]=0;
			for(int c=1;c<C;c++)
			{
				int &m=MAP[r][c][1];
				scanf("%d",&m);
				MAP[r][c+1][3]=m;
			}
			if(r==R)break;
			for(int c=1;c<=C;c++)
			{
				int &m=MAP[r][c][2];
				scanf("%d",&m);
				MAP[r+1][c][0]=m;
			}
		}
		int ans=solve();
		printf("Case %d: ",kase++);
		if(ans==2147483647)printf("Impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
