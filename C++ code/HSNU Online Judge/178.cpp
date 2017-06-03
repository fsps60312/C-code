#include<cstdio>
#include<algorithm>
using namespace std;
int N,DP[1000000][2];
char S[1000001];
int main()
{
	static int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%s",&N,S);
		DP[0][0]=(S[0]=='A'?0:1);
		DP[0][1]=(S[0]=='A'?1:0);
		for(int i=1;i<N;i++)
		{
			if(S[i]=='A')
			{
				DP[i][0]=min(DP[i-1][0],DP[i-1][1]+2);
				DP[i][1]=min(DP[i-1][0]+1,DP[i-1][1]+1);
			}
			else
			{
				DP[i][0]=min(DP[i-1][0]+1,DP[i-1][1]+1);
				DP[i][1]=min(DP[i-1][0]+2,DP[i-1][1]);
			}
		}
		printf("%d\n",DP[N-1][0]);
	}
	return 0;
}
