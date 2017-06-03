#include<cstdio>
#include<cstdlib>
#define LL long long
#include<queue>
using namespace std;
int N,M;
LL MAP[1001][1001][3],BEST[1001][1001][2];
short INQ[1001][1001][2];
struct PqType
{
	int r,c,d;
	bool operator<(PqType a)const{return BEST[r][c][d]>BEST[a.r][a.c][a.d];}
};
bool getmin(LL &a,LL b){if(b<a){a=b;return true;}return false;}
LL solve()
{
	for(int r=0;r<N;r++)
	{
		for(int c=1;c<=M;c++)
		{
			BEST[r][c][0]=BEST[r][c][1]=9223372036854775807LL;
			INQ[r][c][0]=INQ[r][c][1]=0;
		}
	}
	priority_queue<PqType> pq;
	for(int r=1;r<N;r++)
	{
		BEST[r][1][0]=MAP[r][1][2];
		pq.push((PqType){r,1,0});
		INQ[r][1][0]=1;
	}
	if(BEST[N-1][1][0]>MAP[N][1][0])BEST[N-1][1][0]=MAP[N][1][0];
	for(int c=2;c<M;c++)
	{
		BEST[N-1][c][0]=MAP[N][c][0];
		pq.push((PqType){N-1,c});
		INQ[N-1][c][0]=1;
	}
	LL ans=9223372036854775807LL;
	while(!pq.empty())
	{
		PqType p=pq.top();pq.pop();
		INQ[p.r][p.c][p.d]=0;
		LL &best=BEST[p.r][p.c][p.d];
		if(p.d==1)
		{
			if(p.r==0||p.c==M)getmin(ans,best);
			if(getmin(BEST[p.r][p.c][0],best+MAP[p.r][p.c][1])&&!INQ[p.r][p.c][0])
			{
				INQ[p.r][p.c][0]=1;
				pq.push((PqType){p.r,p.c,0});
			}
			if(p.r>0&&getmin(BEST[p.r-1][p.c][0],best+MAP[p.r][p.c][0])&&!INQ[p.r-1][p.c][0])
			{
				INQ[p.r-1][p.c][0]=1;
				pq.push((PqType){p.r-1,p.c,0});
			}
			if(p.c<M&&getmin(BEST[p.r][p.c+1][0],best+MAP[p.r][p.c+1][2])&&!INQ[p.r][p.c+1][0])
			{
				INQ[p.r][p.c+1][0]=1;
				pq.push((PqType){p.r,p.c+1,0});
			}
		}
		else
		{
			if(getmin(BEST[p.r][p.c][1],best+MAP[p.r][p.c][1])&&!INQ[p.r][p.c][1])
			{
				INQ[p.r][p.c][1]=1;
				pq.push((PqType){p.r,p.c,1});
			}
			if(p.c>1&&getmin(BEST[p.r][p.c-1][1],best+MAP[p.r][p.c][2])&&!INQ[p.r][p.c-1][1])
			{
				INQ[p.r][p.c-1][1]=1;
				pq.push((PqType){p.r,p.c-1,1});
			}
			if(p.r<N-1&&getmin(BEST[p.r+1][p.c][1],best+MAP[p.r+1][p.c][0])&&!INQ[p.r+1][p.c][1])
			{
				INQ[p.r+1][p.c][1]=1;
				pq.push((PqType){p.r+1,p.c,1});
			}
		}
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int r=1;r<=N;r++)
		{
			for(int c=1;c<M;c++)
			{
				scanf("%lld",&MAP[r][c][0]);
			}
		}
		for(int r=1;r<N;r++)
		{
			for(int c=1;c<=M;c++)
			{
				scanf("%lld",&MAP[r][c][2]);
			}
		}
		for(int r=1;r<N;r++)
		{
			for(int c=1;c<M;c++)
			{
				scanf("%lld",&MAP[r][c][1]);
			}
		}
		printf("Case %d: Minimum = %lld\n",kase++,solve());
	}
	return 0;
}
