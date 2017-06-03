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
bool VIS[21][21][10][10][10][10];
char MAP[21][22];
void getmin(int &a,int b){if(b<a)a=b;}
struct Way
{
	int x,y,v0,v1,v2,v3,v;
	Way(){}
	int R(int x,int y){return MAP[y][x]==CR?1:0;}
	Way(int x,int y,int v0,int v1,int v2,int v3):x(x),y(y)
	,v0(v0+R(x,y)),v1(v1+R(N-1-y,x)),v2(v2+R(N-1-x,N-1-y)),v3(v3+R(y,N-1-x))
	,v(max(max(v0,v1),max(v2,v3))){}
	bool AtRim(){return x==0||y==0||x==N-1||y==N-1;}
};
int solve()
{
//	static vector<Way>change;
//	for(int i=0;i<change.size();i++)
//	{
//		Way &c=change[i];
//		VIS[c.y][c.x][c.v0][c.v1][c.v2][c.v3]=false;
//	}
//	change.clear();
	for(int a=0;a<N;a++)for(int b=0;b<N;b++)
	for(int c=0;c<N/2;c++)for(int d=0;d<N/2;d++)for(int e=0;e<N/2;e++)for(int f=0;f<N/2;f++)VIS[a][b][c][d][e][f]=false;
	queue<Way>q;
	q.push(Way(N/2,N/2,0,0,0,0));
	int ans=INF;
	while(!q.empty())
	{
		Way w=q.front();q.pop();
		int &x=w.x,&y=w.y,&v0=w.v0,&v1=w.v1,&v2=w.v2,&v3=w.v3;
		if(w.AtRim()){getmin(ans,w.v);continue;}
		if(VIS[y][x][v0][v1][v2][v3])continue;
		VIS[y][x][v0][v1][v2][v3]=true;
//		change.push_back(w);
		q.push(Way(x-1,y,v0,v1,v2,v3));
		q.push(Way(x+1,y,v0,v1,v2,v3));
		q.push(Way(x,y-1,v0,v1,v2,v3));
		q.push(Way(x,y+1,v0,v1,v2,v3));
	}
	return ans;
}
int main()
{
	for(int a=0;a<21;a++)for(int b=0;b<21;b++)
	for(int c=0;c<10;c++)for(int d=0;d<10;d++)for(int e=0;e<10;e++)for(int f=0;f<10;f++)VIS[a][b][c][d][e][f]=false;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				char &v=MAP[i][j];
				do{scanf("%c",&v);}while(v!=CR&&v!=CP&&v!=CE);
			}
		}
		printf("At most %d rose(s) trampled.\n",solve());
	}
	return 0;
}
