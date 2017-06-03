#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
#define debug(...) ;//__VA_ARGS__
int R,C,AL;
int ANS[30][2],TANS[30][2];
char S[17][17];
bool DV[17][17],BV[17][17];
bool isnum(char a){return a>='0'&&a<='9';}
void copyans(int l){AL=l;for(int i=0;i<=l;i++)ANS[i][0]=TANS[i][0],ANS[i][1]=TANS[i][1];}
char SANS(int i){return S[ANS[i][0]][ANS[i][1]];}
char STANS(int i){return S[TANS[i][0]][TANS[i][1]];}
int D[4][2]={1,0,-1,0,0,1,0,-1};
int bfs(int r0,int c0)
{
	for(int i=1;i<=R;i++)
	{
		for(int j=1;j<=C;j++)
		{
			BV[i][j]=DV[i][j];
		}
	}
	queue<int> q;
	BV[r0][c0]=true;
	int ans=0,ta=0;
	for(int i=0;i<4;i++)
	{
		q.push(r0+D[i][0]),q.push(c0+D[i][1]);
		while(!q.empty())
		{
			int r=q.front();q.pop();
			int c=q.front();q.pop();
			if(!S[r][c]||BV[r][c])continue;
			ta++;
			BV[r][c]=true;
			q.push(r+1),q.push(c);
			q.push(r-1),q.push(c);
			q.push(r),q.push(c+1);
			q.push(r),q.push(c-1);
		}
		if(ta>ans)ans=ta;
	}
	return ans;
}
bool ok(int r,int c){return !DV[r][c]&&S[r][c];}
void dfs(int r,int c,int dep,int last)//0:up,1:down,2:right,3:left
{
	if(!ok(r,c))return;
	if(last!=-1&&!ok(r+D[last^1][0],c+D[last^1][0]))
	{
		int len=dep+bfs(r,c);
		if(len<AL)return;
		else if(len==AL)
		{
			for(int i=0;i<dep;i++)
			{
				if(SANS(i)>STANS(i))return;
				else if(SANS(i)<STANS(i))break;
			}
		}
	}
	DV[r][c]=true;
	TANS[dep][0]=r,TANS[dep][1]=c;
	if(dep>AL)copyans(dep);
	else if(dep==AL)
	{
		for(int i=0;i<=AL;i++)
		{
			if(SANS(i)>STANS(i))break;
			else if(SANS(i)<STANS(i)){copyans(dep);break;}
		}
	}
	dep++;
	for(int i=0;i<4;i++)
	{
		int j=(last+1+i)%4;
		dfs(r+D[j][0],c+D[j][1],dep,j);
	}
	DV[r][c]=false;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d",&R,&C)==2&&(R||C))
	{
		for(int i=1;i<=R;i++)S[i][0]=S[i][C+1]=0;
		for(int i=1;i<=C;i++)S[0][i]=S[R+1][i]=0;
		for(int i=1;i<=R;i++)
		{
			for(int j=1;j<=C;j++)
			{
				char &c=S[i][j];
				do
				{
					scanf("%c",&c);
				}while(c!='#'&&!isnum(c));
				DV[i][j]=false;
				if(c=='#')c=0;
			}debug(printf("\"%s\"\n",S[i]+1););
		}
		AL=-1;
		for(int i=1;i<=R;i++)
		{
			for(int j=1;j<=C;j++)
			{
				//printf("%d %d\n",i,j);
				dfs(i,j,0,-1);
			}
		}debug(printf("AL=%d\n",AL););
		for(int i=0;i<=AL;i++)printf("%c",SANS(i));printf("\n");
	}
	return 0;
}
