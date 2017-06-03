#include<cstdio>
#include<queue>
#include<cassert>
#include<vector>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
short Q,R,C;
short VIS[1000][1000],LAKE[1000][1000];
struct Edge
{
	short r,c,dis,cost;
	Edge(){}
	Edge(short &r,short &c,short dis,short cost):r(r),c(c),dis(dis),cost(cost){}
	bool operator<(const Edge &a)const{if(dis!=a.dis)return dis>a.dis;return cost>a.cost;}
};
int Dis(short r1,short c1,short r2,short c2)
{
	static priority_queue<Edge,vector<Edge> >pq;
	while(!pq.empty())pq.pop();
	pq.push(Edge(r1,c1,0,r2-r1+c2-c1));
	static Edge e,ne;
	static short &r=e.r,&c=e.c,&dis=e.dis,&y=ne.r,&x=ne.c;
	static short i;
	static short dy[8]={-1,-1,0,1,1,1,0,-1};
	static short dx[8]={0,1,1,1,0,-1,-1,-1};
	while(!pq.empty())
	{
		e=pq.top();pq.pop();
		if(r==r2&&c==c2)return dis;
		VIS[r][c]=Q;
		for(i=0;i<8;i++)
		{
			y=r+dy[i],x=c+dx[i];
			if(y<0||x<0||y>=R||x>=C||VIS[y][x]==Q)continue;
			ne.dis=dis;
			if(i!=LAKE[r][c])ne.dis++;
			ne.cost=r2-y+c2-x;
			pq.push(ne);
		}
	}
	termin("can't find path\n");
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int t1,t2;
	while(scanf("%d%d",&t1,&t2)==2)
	{
		R=t1,C=t2;
		short r,c,i;
		for(r=0;r<R;r++)
		{
			for(c=0;c<C;c++)
			{
				static char v;
				VIS[r][c]=-1;
				do{if(scanf("%c",&v)!=1)return 0;}while(v<'0'||v>'7');
				LAKE[r][c]=v-'0';
			}
		}
		scanf("%d",&t1);Q=t1;
		while(Q--)
		{
			static int r1,c1,r2,c2;
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			r1--,c1--,r2--,c2--;
			printf("%d\n",Dis(r1,c1,r2,c2));
		}
	}
	return 0;
}
