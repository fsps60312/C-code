#include<cstdio>
#include<queue>
#include<cassert>
#include<algorithm>
#include<set>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
const int INF=2147483647;
const char CR='R',CE='.',CP='P';
int N;
bool VIS[21][21][11][11][11][11];
char MAP[21][21];
void getmin(int &a,int b){if(b<a)a=b;}
struct Way
{
	int x,y,v0,v1,v2,v3,v;
	Way(){}
	int R(int x,int y){return MAP[y][x]==CR?1:0;}
	Way(int _x,int _y,int _v0,int _v1,int _v2,int _v3):x(_x),y(_y),v0(_v0),v1(_v1),v2(_v2),v3(_v3)
	{
		v0+=R(x,y);
		v1+=R(N-1-y,x);
		v2+=R(N-1-x,N-1-y);
		v3+=R(y,N-1-x);
		v=max(max(v0,v1),max(v2,v3));
	}
	bool AtRim(){return x==0||y==0||x==N-1||y==N-1;}
	bool operator<(const Way &w)const{return v>w.v;}
};
bool &Vis(Way w){return VIS[w.y][w.x][w.v0][w.v1][w.v2][w.v3];}
void TryPush(Way w,priority_queue<Way>&pq)
{
	if(Vis(w))return;
	Vis(w)=true;
	pq.push(w);
}
int solve(int sx,int sy)
{
//	for(int a=0;a<21;a++)for(int b=0;b<21;b++)
//	for(int c=0;c<=10;c++)for(int d=0;d<=10;d++)for(int e=0;e<=10;e++)for(int f=0;f<=10;f++)VIS[a][b][c][d][e][f]=false;
	for(int a=0;a<N;a++)for(int b=0;b<N;b++)
	for(int c=0;c<=N/2;c++)for(int d=0;d<=N/2;d++)for(int e=0;e<=N/2;e++)for(int f=0;f<=N/2;f++)VIS[a][b][c][d][e][f]=false;
	priority_queue<Way>q;
	TryPush(Way(sx,sy,0,0,0,0),q);
	while(!q.empty())
	{
		Way w=q.top();q.pop();
		int &x=w.x,&y=w.y,&v0=w.v0,&v1=w.v1,&v2=w.v2,&v3=w.v3;
		if(w.AtRim())return w.v;
		if(x<0||y<0||x>=N||y>=N||w.v>N/2)termin("out of range\n");
		TryPush(Way(x-1,y,v0,v1,v2,v3),q);
		TryPush(Way(x+1,y,v0,v1,v2,v3),q);
		TryPush(Way(x,y-1,v0,v1,v2,v3),q);
		TryPush(Way(x,y+1,v0,v1,v2,v3),q);
	}
	termin("can't reach rim\n");
}
int main()
{
	for(int a=0;a<21;a++)for(int b=0;b<21;b++)
	for(int c=0;c<=10;c++)for(int d=0;d<=10;d++)for(int e=0;e<=10;e++)for(int f=0;f<=10;f++)VIS[a][b][c][d][e][f]=false;
	while(scanf("%d",&N)==1&&N)
	{
		if(N>21)termin("N==%d\n",N);
		int x=-1,y=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				char &v=MAP[i][j];
				do{scanf("%c",&v);}while(v!=CR&&v!=CP&&v!=CE);
				if(v==CP)x=j,y=i;
			}
		}
		if(x==-1)termin("can't find start point\n");
		printf("At most %d rose(s) trampled.\n",solve(x,y));
	}
	return 0;
}
