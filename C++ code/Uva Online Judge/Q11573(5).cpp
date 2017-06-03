#include<cstdio>
#include<queue>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
int Q,R,C;
short VIS[1000][1000],LAKE[1000][1000];
struct Edge
{
	short r,c,dis;
	Edge(){}
	Edge(short &r,short &c,short dis):r(r),c(c),dis(dis){}
	bool operator<(Edge a)const{return dis>a.dis;}
};
int Dis(short r1,short c1,short r2,short c2)
{
	priority_queue<Edge>pq;
	pq.push(Edge(r1,c1,0));
	while(!pq.empty())
	{
		static Edge e,ne;
		static short &r=e.r,&c=e.c,&dis=e.dis,&y=ne.r,&x=ne.c;
		e=pq.top();pq.pop();
		if(r==r2&&c==c2)return dis;
		VIS[r][c]=Q;
		static short d[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
		ne=e;
		for(short i=0;i<8;i++)
		{
			y=r+d[i][0],x=c+d[i][1];
			if(y<0||x<0||y>=R||x>=C||VIS[y][x]==Q)continue;
			ne.dis=dis;
			if(i!=LAKE[r][c])ne.dis++;
			pq.push(ne);
		}
	}
	termin("can't find path\n");
}
int main()
{
	while(scanf("%d%d",&R,&C)==2)
	{
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
		scanf("%d",&Q);
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
