#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char S[27][27];
bool vis[27][27][4][5];//up,right,down,left
void setvis(int r,int c,bool v)
{
	for(int d=0;d<4;d++)
	{
		for(int i=0;i<5;i++)
		{
			vis[r][c][d][i]=v;
		}
	}
}
int D[4][2]={-1,0,0,1,1,0,0,-1},M,N;
struct Pair{int r,c,d,i,v;bool operator==(Pair a){return r==a.r&&c==a.c&&i==a.i;}};
int main()
{
	int kase=1;
	Pair target,now;
	while(scanf("%d%d",&M,&N)==2&&(M||N))
	{
		if(kase>1)printf("\n");
		queue<Pair> q;
		for(int c=1;c<=N;c++)setvis(0,c,true),setvis(M+1,c,true);
		for(int r=1;r<=M;r++)
		{
			setvis(r,0,true),setvis(r,N+1,true);
			for(int c=1;c<=N;c++)
			{
				char &t=S[r][c];
				do
				{
					scanf("%c",&t);
				}while(t!='.'&&t!='S'&&t!='T'&&t!='#');
				if(t=='#')setvis(r,c,true);
				else setvis(r,c,false);
				if(t=='T')target.r=r,target.c=c,target.i=0;
				if(t=='S')
				{
					q.push((Pair){r,c,0,0,0});
				}
			}
		}
		now=(Pair){0,0,0,0,0};
		while(!q.empty())
		{
			now=q.front();q.pop();
			if(now==target)break;
			bool &tv=vis[now.r][now.c][now.d][now.i];
			if(tv)continue;
			tv=true;
			q.push((Pair){now.r+D[now.d][0],now.c+D[now.d][1],now.d,(now.i+1)%5,now.v+1});
			q.push((Pair){now.r,now.c,(now.d+1)%4,now.i,now.v+1});
			q.push((Pair){now.r,now.c,(now.d+3)%4,now.i,now.v+1});
		}
		printf("Case #%d\n",kase++);
		if(now==target)printf("minimum time = %d sec\n",now.v);
		else printf("destination not reachable\n");
	}
	return 0;
}
