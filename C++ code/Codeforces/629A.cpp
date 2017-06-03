#include<cstdio>
#include<cassert>
using namespace std;
int N;
char S[100][101];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%s",S[i]);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			int cnt=0;
			for(int j=0;j<N;j++)if(S[i][j]=='C')cnt++;
			ans+=cnt*(cnt-1)/2;
			cnt=0;
			for(int j=0;j<N;j++)if(S[j][i]=='C')cnt++;
			ans+=cnt*(cnt-1)/2;
		}
		printf("%d\n",ans);
	}
	return 0;
}
