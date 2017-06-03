#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[100000];
int DP[100000][2];
int main()
{
//	freopen("in.txt","r",stdin);
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		DP[0][0]=0,DP[0][1]=S[0];
		for(int i=1;i<N;i++)
		{
			DP[i][0]=max(DP[i-1][0],DP[i-1][1]);
			DP[i][1]=DP[i-1][0]+S[i];
		}
		printf("%d\n",max(DP[N-1][0],DP[N-1][1]));
	}
	return 0;
}
