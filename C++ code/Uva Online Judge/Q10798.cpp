#include<cstdio>
#include<queue>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
const char CR='R',CE='.',CP='P';
int N;
char MAP[21][22];
bool VIS[21][21];
int max(int a,int b){return a>b?a:b;}
struct Way
{
	int x,y,v0,v1,v2,v3;
	Way(){}
	int R(int x,int y){if(this->x==-2||VIS[y][x]){this->x=-2;return -1;}VIS[y][x]=true;return MAP[y][x]==CR?1:0;}
	Way(int x,int y,int v0,int v1,int v2,int v3):x(x),y(y),v0(v0+R(x,y)),v1(v1+R(N-1-y,x)),v2(v2+R(N-1-x,N-1-y)),v3(v3+R(y,N-1-x)){}
	int GetValue()const{return max(max(v0,v1),max(v2,v3));}
	bool AtRim(){return x==0||y==0||x==N-1||y==N-1;}
	bool operator<(Way a)const{return GetValue()>a.GetValue();}
};
int solve()
{
	priority_queue<Way>pq;
	Way s;
	s.x=s.y=N/2;
	s.v0=s.v1=s.v2=s.v3=0;
	pq.push(s);
	VIS[N/2][N/2]=true;
	while(!pq.empty())
	{
		Way w=pq.top();pq.pop();
		if(w.x==-2)continue;
		if(w.AtRim())return w.GetValue();
		int &x=w.x,&y=w.y,&v0=w.v0,&v1=w.v1,&v2=w.v2,&v3=w.v3;
		pq.push(Way(x-1,y,v0,v1,v2,v3));
		pq.push(Way(x+1,y,v0,v1,v2,v3));
		pq.push(Way(x,y-1,v0,v1,v2,v3));
		pq.push(Way(x,y+1,v0,v1,v2,v3));
	}
	termin("Can't reach rim\n");
}
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
				VIS[i][j]=false;
			}
		}
		printf("At most %d rose(s) trampled.\n",solve());
	}
	return 0;
}
