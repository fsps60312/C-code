#include<cstdio>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,TWO[1000][1000],FIVE[1000][1000];
bool VIS[1000][1000];
struct Pq
{
	int x,y,two,five;
	Pq(){}
	Pq(const int &x,const int &y,const int &t,const int &f):x(x),y(y),two(t),five(f){}
	bool operator<(const Pq &p)const{return min(two,five)>min(p.two,p.five);}
};
int Solve()
{
	priority_queue<Pq>pq;
	pq.push(Pq(0,0,TWO[0][0],FIVE[0][0]));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.x][p.y])continue;
		VIS[p.x][p.y]=true;
		static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
		for(int i=0;i<4;i++)
		{
			int x=p.x+d[i][0],y=p.y+d[i][1];
			if(x<0||y<0||x>=N||y>=N)continue;
			pq.push(Pq(x,y,p.two+TWO[x][y],p.five+FIVE[x][y]));
		}
	}
	assert(0);
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			static int v;
			scanf("%d",&v);
			VIS[i][j]=false;
			TWO[i][j]=FIVE[i][j]=0;
			while(v&&v%2==0)v/=2,TWO[i][j]++;
			while(v&&v%5==0)v/=5,FIVE[i][j]++;
		}
	}
	printf("%d\n",Solve());
	return 0;
}
