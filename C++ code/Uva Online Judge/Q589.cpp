#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char MAP[22][22];
struct Point
{
	int r,c;
}SP,BP;
struct Pre
{
	int sr,sc,br,bc;
	Pre move(int o)
	{
		int d[4][2]={-1,0,1,0,0,-1,0,1};
		Pre ans=(Pre){sr,sc,br,bc};
		ans.sr+=d[o][0];
		ans.sc+=d[o][1];
		if(ans.br==ans.sr&&ans.bc==ans.sc)
		{
			ans.br+=d[o][0];
			ans.bc+=d[o][1];
		}
		return ans;
	}
	int pushed(int o)
	{
		int d[4][2]={-1,0,1,0,0,-1,0,1};
		Pre ans=(Pre){sr,sc,br,bc};
		ans.sr+=d[o][0];
		ans.sc+=d[o][1];
		if(ans.br==ans.sr&&ans.bc==ans.sc)return 1;
		return 0;
	}
};
Pre PRE[21][21][21][21];
int MOVE[21][21][21][21];
Pre &get_PRE(Pre a){return PRE[a.sr][a.sc][a.br][a.bc];}
int &get_MOVE(Pre a){return MOVE[a.sr][a.sc][a.br][a.bc];}
int R,C;
bool check_PRE(Pre a)
{
	return a.sc>=1&&a.sc<=C
	&&a.sr>=1&&a.sr<=R
	&&a.bc>=1&&a.bc<=C
	&&a.br>=1&&a.br<=R
	&&MAP[a.sr][a.sc]!='#'
	&&MAP[a.br][a.bc]!='#';
}
struct Trip
{
	Pre now,pre;
	int o,step,ps;
	bool operator<(Trip a)const
	{
		if(step!=a.step)
		return step>a.step;
		if(ps!=a.ps)
		return ps>a.ps;
		//if(o!=a.o)
		return o>a.o;
	}
};
void dfs_print(Pre u)
{
	if(get_MOVE(u)==-1)return;
	Pre &pre=get_PRE(u);
	dfs_print(pre);
	char ans;
	switch(get_MOVE(u))
	{
		case 0:ans='n';break;
		case 1:ans='s';break;
		case 2:ans='w';break;
		default:ans='e';break;
	}
	if(u.bc!=pre.bc||u.br!=pre.br)ans+='A'-'a';
	printf("%c",ans);
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d",&R,&C)==2&&(R||C))
	{
		for(int c=1;c<=C;c++)MAP[0][c]=MAP[R+1][c]='#';
		for(int r=1;r<=R;r++)
		{
			MAP[r][0]=MAP[r][C+1]='#';
			for(int c=1;c<=C;c++)
			{
				for(int r1=1;r1<=R;r1++)
				{
					for(int c1=1;c1<=C;c1++)
					{
						PRE[r][c][r1][c1]=(Pre){-1,-1,-1,-1};
					}
				}
				char &a=MAP[r][c];
				do
				{
					scanf("%c",&a);
				}while(a!='S'&&a!='B'&&a!='.'&&a!='#'&&a!='T');
				if(a=='S')SP=(Point){r,c};
				else if(a=='B')BP=(Point){r,c};
			}
		}
		priority_queue<Trip> pq;
		pq.push((Trip){(Pre){SP.r,SP.c,BP.r,BP.c},(Pre){-2,-1,-1,-1},-1,0,0});
		Trip ans;
		while(!pq.empty())
		{
			ans=pq.top();pq.pop();
			if(!check_PRE(ans.now))continue;
			Pre &now=get_PRE(ans.now);
			if(now.sr!=-1)continue;
			get_MOVE(ans.now)=ans.o;
			now=ans.pre;
			//printf("(%d,%d)(%d,%d)%d\n",ans.now.sr,ans.now.sc,ans.now.br,ans.now.bc,ans.step);
			//printf("%c\n",MAP[ans.now.bc][ans.now.br]);
			if(MAP[ans.now.br][ans.now.bc]=='T')break;
			for(int o=0;o<4;o++)
			{
				pq.push((Trip){ans.now.move(o),ans.now,o,ans.step+ans.now.pushed(o),ans.ps+1});
			}
		}
		printf("Maze #%d\n",kase++);
		if(!check_PRE(ans.now)||MAP[ans.now.br][ans.now.bc]!='T')printf("Impossible.");
		else dfs_print(ans.now);
		printf("\n\n");
	}
	return 0;
}
