#include<cstdio>
#include<queue>
#include<cassert>
#include<algorithm>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
const char CR='R',CE='.',CP='P';
int N;
char MAP[21][22];
int VIS[21][21];
struct Way
{
	int x,y,v0,v1,v2,v3;
	Way(){}
	int R(int x,int y){return MAP[y][x]==CR?1:0;}
	Way(int x,int y,int v0,int v1,int v2,int v3):x(x),y(y),v0(v0+R(x,y)),v1(v1+R(N-1-y,x)),v2(v2+R(N-1-x,N-1-y)),v3(v3+R(y,N-1-x)){}
	int GetValue()const{return max(max(v0,v1),max(v2,v3));}
	bool AtRim(){return x==0||y==0||x==N-1||y==N-1;}
	bool operator<(Way w)const
	{
		static int a[4],b[4];
		a[0]=v0,a[1]=v1,a[2]=v2,a[3]=v3;
		b[0]=w.v0,b[1]=w.v1,b[2]=w.v2,b[3]=w.v3;
		sort(a,a+4),sort(b,b+4);
		for(int i=3;i>=0;i--)if(a[i]!=b[i])return a[i]>b[i];
	}
};
int solve()
{
	priority_queue<Way>pq;
	Way s;
	s.x=s.y=N/2;
	s.v0=s.v1=s.v2=s.v3=0;
	pq.push(s);
	while(!pq.empty())
	{
		Way w=pq.top();pq.pop();
		int &x=w.x,&y=w.y,&v0=w.v0,&v1=w.v1,&v2=w.v2,&v3=w.v3;
		if(VIS[y][x]<=w.GetValue())continue;
		VIS[y][x]=VIS[x][N-1-y]=VIS[N-1-y][N-1-x]=VIS[N-1-x][y]=w.GetValue();
		if(w.AtRim())return w.GetValue();
		pq.push(Way(x-1,y,v0,v1,v2,v3));
		pq.push(Way(x+1,y,v0,v1,v2,v3));
		pq.push(Way(x,y-1,v0,v1,v2,v3));
		pq.push(Way(x,y+1,v0,v1,v2,v3));
	}
	termin("Can't reach rim\n");
}
const int INF=2147483647;
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				char &v=MAP[i][j];
				do{scanf("%c",&v);}while(v!=CR&&v!=CP&&v!=CE);
				VIS[i][j]=INF;
			}
		}
		printf("At most %d rose(s) trampled.\n",solve());
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("%c",'0'+(VIS[i][j]==INF?'*'-'0':VIS[i][j]));
			}
			puts("");
		}
	}
	return 0;
}
