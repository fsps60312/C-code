#include<cstdio>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int R,C,GRID[1001][1001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(2,"%d%d",&R,&C);
	for(int i=1;i<=R;i++)
	{
		static char tmp[1001];scanf(1,"%s",tmp);
		for(int j=0;j<C;j++)assert(tmp[j]=='0'||tmp[j]=='1'),GRID[i][j+1]=tmp[j]-'0';
	}
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)GRID[i][j]=GRID[i][j]+GRID[i-1][j]+GRID[i][j-1]-GRID[i-1][j-1];
	int ans=0;
	for(int len=1;len<=R&&len<=C;len++)
	{
		for(int r=1;r+len-1<=R;r++)for(int c=1;c+len-1<=C;c++)
		{
			const int sum=GRID[r+len-1][c+len-1]-GRID[r-1][c+len-1]-GRID[r+len-1][c-1]+GRID[r-1][c-1];
			if(sum==len*len)ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
