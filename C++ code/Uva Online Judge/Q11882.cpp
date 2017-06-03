#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
#define debug(...) __VA_ARGS__
int R,C,AL;
int ANS[30][2],TANS[30][2];
char S[17][17];
bool DV[17][17],BV[17][17];
bool isnum(char a){return a>='0'&&a<='9';}
void copyans(int l){AL=l;for(int i=0;i<=l;i++)ANS[i][0]=TANS[i][0],ANS[i][1]=TANS[i][1];}
char SANS(int i){return S[ANS[i][0]][ANS[i][1]];}
char STANS(int i){return S[TANS[i][0]][TANS[i][1]];}
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
	int ans;
	q.push(r0),q.push(c0),q.push(0);
	while(!q.empty())
	{
		int r=q.front();q.pop();
		int c=q.front();q.pop();
		int d=q.front();q.pop();
		if(!S[r][c]||BV[r][c])continue;
		BV[r][c]=true;
		ans=d++;
		q.push(r+1),q.push(c),q.push(d);
		q.push(r-1),q.push(c),q.push(d);
		q.push(r),q.push(c+1),q.push(d);
		q.push(r),q.push(c-1),q.push(d);
	}
	return ans;
}
void dfs(int r,int c,int dep)
{
	if(DV[r][c]||!S[r][c]||dep+bfs(r,c)<AL)return;
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
	dfs(r+1,c,dep);
	dfs(r-1,c,dep);
	dfs(r,c+1,dep);
	dfs(r,c-1,dep);
	DV[r][c]=false;
}
int main()
{
	freopen("in.txt","r",stdin);
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
				dfs(i,j,0);
			}
		}debug(printf("AL=%d\n",AL););
		for(int i=0;i<=AL;i++)printf("%c",SANS(i));printf("\n");
	}
	return 0;
}
