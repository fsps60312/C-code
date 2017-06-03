#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
int Q,R,C,VIS[1000][1000];
char LAKE[1000][1000];
struct Edge
{
	int r,c,dis;
	Edge(){}
	Edge(int r,int c,int dis):r(r),c(c),dis(dis){}
	bool operator<(Edge a)const{return dis>a.dis;}
};
vector<Edge>TO[1000000];
int Dis(int r1,int c1,int r2,int c2)
{
	priority_queue<Edge>pq;
	pq.push(Edge(r1,c1,0));
	while(!pq.empty())
	{
		Edge e=pq.top();pq.pop();
		int &r=e.r,&c=e.c,&dis=e.dis;
		if(r==r2&&c==c2)return dis;
		if(VIS[r][c]==Q)continue;
		VIS[r][c]=Q;
		static int d[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
		for(int i=0,y,x;i<8;i++)
		{
			y=r+d[i][0],x=c+d[i][1];
			if(y<0||x<0||y>=R||x>=C)continue;
			if(i==LAKE[r][c])pq.push(Edge(y,x,dis));
			else pq.push(Edge(y,x,dis+1));
		}
	}
	termin("can't find path\n");
}
int main()
{
	while(scanf("%d%d",&R,&C)==2)
	{
		for(int r=0;r<R;r++)
		{
			for(int c=0;c<C;c++)
			{
				static char v;
				VIS[r][c]=-1;
				do{scanf("%c",&v);}while(v<'0'||v>'7');
				LAKE[r][c]=v-'0';
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
