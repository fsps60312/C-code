#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,DOWN[1000][1000],RIGHT[1000][1000];
char GRID[1000][1000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		char &c=GRID[i][j];
		do{c=getchar();}while(c!='0'&&c!='1');
	}
	for(int i=N-1;i>=0;i--)for(int j=N-1;j>=0;j--)
	{
		if(GRID[i][j]=='0')DOWN[i][j]=RIGHT[i][j]=0;
		else DOWN[i][j]=(i==N-1?1:DOWN[i+1][j]+1),RIGHT[i][j]=(j==N-1?1:RIGHT[i][j+1]+1);
	}
	int ans=0;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		int mxlen=min(DOWN[i][j],RIGHT[i][j]);
		for(int len=1;len<=mxlen;len++)if(DOWN[i][j+len-1]>=len&&RIGHT[i+len-1][j]>=len)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
