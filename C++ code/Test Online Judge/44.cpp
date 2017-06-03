#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int MAX_COLUMN=65501;
int R;
char S[100][MAX_COLUMN];
bool VIS[100][MAX_COLUMN];
void Solve()
{
	queue<int>q;
	for(int i=0;i<R;i++)for(int j=0;S[i][j];j++)
	{
		if(S[i][j]=='K')q.push(i),q.push(j),q.push(0);
		VIS[i][j]=false;
	}
	assert((int)q.size()==3);
	while(!q.empty())
	{
		const int r=q.front();q.pop();
		const int c=q.front();q.pop();
		const int dist=q.front();q.pop();
		if(S[r][c]=='#'||VIS[r][c])continue;
		VIS[r][c]=true;
		if(S[r][c]=='@'){printf("%d\n",dist);return;}
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)q.push(r+d[i][0]),q.push(c+d[i][1]),q.push(dist+1);
	}
	puts("= =\"");
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&R)==1&&R)
	{
		for(int i=0;i<R;i++)scanf("%s",S[i]);
		Solve();
	}
	return 0;
}
