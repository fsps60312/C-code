#include<cstdio>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N;
char S[2][1002];
int main()
{
	freopen("Bin","r",stdin);
	freopen("out.txt","w",stdout);
	static int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(1,"%d",&N);
		assert(N<=1000);
		scanf(2,"%s%s",S[0]+1,S[1]+1);
		S[0][0]=S[1][0]=S[0][N+1]=S[1][N+1]='X';
		for(int d=0;d<2;d++)for(int i=0;i<=N+1;i++)assert(S[d][i]=='X'||S[d][i]=='.');
		int ans=0;
		for(int d=0;d<2;d++)
		{
			for(int i=1;i<=N;i++)
			{
				if(S[d][i-1]=='X'&&S[d][i]=='.'&&S[d][i+1]=='X')
				{
					S[d][i]='X',ans++;
					if(S[d^1][i]=='.')
					{
						S[d^1][i]='X';
						for(int j=i+1;S[d^1][j]=='.';j++)S[d^1][j]='X';
						for(int j=i-1;S[d^1][j]=='.';j--)S[d^1][j]='X';
					}
				}
			}
		}
		for(int d=0;d<2;d++)
		{
			for(int i=1;i<=N;i++)if(S[d][i]=='.')
			{
				ans++;
				for(int j=i;S[d][j]=='.';j++)S[d][j]='X';
			}
		}
		for(int d=0;d<2;d++)for(int i=0;i<=N+1;i++)assert(S[d][i]=='X');
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
