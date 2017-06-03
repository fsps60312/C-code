#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
int Q,R,C,A,VIS[1000000];
char LAKE[1000000];
struct Edge
{
	int to,dis;
	Edge(){}
	Edge(int to,int dis):to(to),dis(dis){}
	bool operator<(Edge a)const{return dis>a.dis;}
};
vector<Edge>TO[1000000];
int Dis(int s,int t)
{
	priority_queue<Edge>pq;
	pq.push(Edge(s,0));
	while(!pq.empty())
	{
		Edge e=pq.top();pq.pop();
		if(e.to==t)return e.dis;
		if(VIS[e.to]==Q)continue;
		VIS[e.to]=Q;
		for(int i=0;i<TO[e.to].size();i++)
		{
			Edge &ne=TO[e.to][i];
			pq.push(Edge(ne.to,e.dis+ne.dis));
		}
	}
	termin("can't find path\n");
}
int main()
{
	while(scanf("%d%d",&R,&C)==2)
	{
		A=R*C;
		for(int i=0;i<A;i++)
		{
			TO[i].clear();
			VIS[i]=-1;
			char &v=LAKE[i];
			do{scanf("%c",&v);}while(v<'0'||v>'7');
		}
		for(int r=0,x,y;r<R;r++)
		{
			for(int c=0;c<C;c++)
			{
				char &v=LAKE[r*C+c];
				y=r,x=c;
				if(v>='1'&&v<='3')x++;
				if(v>='3'&&v<='5')y++;
				if(v>='5'&&v<='7')x--;
				if(v>='7'||v<='1')y--;
				static int d[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
				for(int i=0;i<8;i++)
				{
					y=r+d[i][0],x=c+d[i][1];
					if(x<0||y<0||x>=C||y>=R)continue;
					TO[r*C+c].push_back(Edge(y*C+x,(v=='0'+i)?0:1));
				}
			}
		}
		scanf("%d",&Q);
		while(Q--)
		{
			static int r1,c1,r2,c2;
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			r1--,c1--,r2--,c2--;
			printf("%d\n",Dis(r1*C+c1,r2*C+c2));
		}
	}
	return 0;
}
