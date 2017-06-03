#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct pairtype
{
	int n;
	int x;
	int y;
};
char S[1001];
pairtype state[1000][1000];
int n;
pairtype ans;
bool cmp(int a,int b,int c,int d)
{
	if(state[a][b].n!=state[c][d].n) return state[a][b].n>state[c][d].n;
	while(a>=0&&b>=0)
	{
		if(S[a]!=S[c]) return S[a]<S[c]; 
		pairtype e=state[a][b];
		a=e.x,b=e.y;
		e=state[c][d];
		c=e.x,d=e.y;
	}
	return false;
}
pairtype search(int a,int b)
{
	pairtype c;
	if(S[a]!=S[b])
	{
		c.x=c.y=-1;
		c.n=0;
		return c;
	}
	c.x=c.y=a+1;
	for(int i=a+1;i<b;i++)
	{
		for(int j=i;j<b;j++)
		{
			if(cmp(i,j,c.x,c.y)) c.x=i,c.y=j;
		}
	}
	c.n=state[c.x][c.y].n+2;
	return c;
}
bool showans(pairtype a)
{
	if(a.x==a.y&&a.y<0)
	{
		if(a.x==-1) return false;
		return true;
	}
	printf("%c",S[a.x]);
	if(showans(state[a.x][a.y]))
	{
		printf("%c",S[a.x]);
	}
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		n=-1;
		while(S[++n]);
		ans.x=ans.y=0;
		for(int i=0;i<n;i++)
		{
			state[i][i].n=1;
			state[i][i].x=state[i][i].y=-1;
			if(cmp(i,i,ans.x,ans.y)) ans.x=i,ans.y=i;
		}
		for(int i=1;i<n;i++)
		{
			if(S[i-1]==S[i])
			{
				state[i-1][i].n=2;
				state[i-1][i].x=-2;
				state[i-1][i].y=-2;
				if(cmp(i-1,i,ans.x,ans.y)) ans.x=i-1,ans.y=i;
			}
			else
			{
				state[i-1][i]=search(i-1,i);
			}
		}
		for(int i=2;i<n;i++)
		{
			for(int j=0;j+i<n;j++)
			{
				state[j][j+i]=search(j,j+i);
				if(cmp(j,j+i,ans.x,ans.y)) ans.x=j,ans.y=j+i;
			}
		}
		//printf("%d %d\n",ans.x,ans.y);
		showans(ans);
		printf("\n");
	}
	return 0;
}
