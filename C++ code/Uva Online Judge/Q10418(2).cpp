#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
struct Hungary
{
	bool VA[100],VB[101];
	int N,BOUND,MATCH[101],EDGE[100][101];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<=N;nxt++)if(EDGE[u][nxt]<=BOUND)
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int Solve(const int bound)
	{
		BOUND=bound;
		int ans=0;
		for(int i=0;i<=N;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=false;
			for(int j=0;j<=N;j++)VB[j]=false;
			if(Match(i))ans++;
		}
		return ans;
	}
}HUNGARY;
vector<int>SOLDIER,TARGET;
int R,C,N;
int H[10000];
int VIS[10000],VIS_CNT;
struct Pq
{
	int u,d,cost;
	Pq(){}
	Pq(const int _u,const int _d,const int _c):u(_u),d(_d),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int GetDirection(const int d,const int h1,const int h2)
{
	if(h1==h2)return d;
	return h2>h1;
}
void GetDis(const int source,const int direction,int *dist)
{
	for(int i=0;i<R*C;i++)dist[i]=-1;
	VIS_CNT++;
	priority_queue<Pq>pq;
	pq.push(Pq(source,direction,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.u]==VIS_CNT)continue;
		VIS[p.u]=VIS_CNT;
		dist[p.u]=p.cost;
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			const int nxtr=p.u/C+d[i][0],nxtc=p.u%C+d[i][1];
			if(nxtr>=0&&nxtr<R&&nxtc>=0&&nxtc<C)
			{
				const int nxtu=nxtr*C+nxtc;
				const int nxtd=GetDirection(p.d,H[p.u],H[nxtu]);
				pq.push(Pq(nxtu,nxtd,p.d==nxtd?p.cost:p.cost+1));
			}
		}
	}
	for(int i=0;i<R*C;i++)assert(dist[i]!=-1);
}
bool Solve(const int bound)
{
	const int noneed=HUNGARY.Solve(bound)+1;
//	printf("bound=%d, noneed=%d, N*2+1=%d\n",bound,noneed,N*2+1);
	return noneed+bound>=N*2+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<10000;i++)VIS[i]=0;VIS_CNT=0;
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		static int targetcount;
		assert(scanf("%d%d%d%d",&R,&C,&N,&targetcount)==4);
		SOLDIER.clear(),TARGET.clear();
		for(int i=0,y,x;;i++)
		{
			assert(scanf("%d%d",&y,&x)==2),y--,x--;
			assert(y>=0&&y<R&&x>=0&&x<C);
			if(i==N*2)break;
			SOLDIER.push_back(y*C+x);
		}
		while(targetcount--)
		{
			static int x,y,r;
			assert(scanf("%d%d%d",&y,&x,&r)==3),y--,x--;
			assert(y>=0&&y<R&&x>=0&&x<C);
			while(r--)TARGET.push_back(y*C+x);
		}
		assert((int)SOLDIER.size()==N*2&&(int)TARGET.size()==N*2+1);
		for(int i=0;i<R*C;i++)assert(scanf("%d",&H[i])==1);
		for(int i=0;i<N*2;i++)
		{
			static int dist[10000];
			GetDis(SOLDIER[i],i<N?1:0,dist);
			for(int j=0;j<=N*2;j++)HUNGARY.EDGE[i][j]=dist[TARGET[j]];
		}
		HUNGARY.N=N*2;
		int lans=0,rans=N*2;
		while(lans<rans)
		{
			const int mid=(lans+rans)/2;
			if(Solve(mid))rans=mid;
			else lans=mid+1;
		}
		printf("%d\n",rans);
	}
	return 0;
}
