#include<cstdio>
#include<queue>
#include<cassert>
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
short Abs(short a){return a>=0?a:-a;}
int Dis(short r1,short c1,short r2,short c2)
{
	static priority_queue<Edge,vector<Edge> >pq;
	pq=priority_queue<Edge,vector<Edge> >();
	pq.push(Edge(r1,c1,0,Abs(r1-r2)+Abs(c1-c2)));
	static Edge e,ne;
	static short &r=e.r,&c=e.c,&dis=e.dis,&y=ne.r,&x=ne.c;
	static short d[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
	static short i;
	while(!pq.empty())
	{
		e=pq.top();pq.pop();
		if(r==r2&&c==c2)return dis;
		VIS[r][c]=Q;
		for(i=0;i<8;i++)
		{
			y=r+d[i][0],x=c+d[i][1];
			if(y<0||x<0||y>=R||x>=C||VIS[y][x]==Q){continue;}
			ne.dis=dis;
			if(i!=LAKE[r][c])ne.dis++;
			ne.cost=Abs(y-r2)+Abs(x-c2);
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
		for(short r=0;r<R;r++)
		{
			for(short c=0;c<C;c++)
			{
				static short v,lowb='0',upb='7';
				VIS[r][c]=-1;
				do{v=getchar();}while(v<lowb||v>upb);
				LAKE[r][c]=v-lowb;
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
