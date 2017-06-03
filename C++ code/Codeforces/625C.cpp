#include<cstdio>
#include<cassert>
using namespace std;
int N,K,ANS[500][500];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		K--;
		int now=N*N;
		for(int i=0;i<N;i++)
		{
			for(int j=N-1;j>=K;j--)ANS[i][j]=now--;
		}
		for(int i=0;i<N;i++)for(int j=K-1;j>=0;j--)ANS[i][j]=now--;
		assert(now==0);
		int ans=0;
		for(int i=0;i<N;i++)ans+=ANS[i][K];
		printf("%d\n",ans);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(j)putchar(' ');
				printf("%d",ANS[i][j]);
			}
			puts("");
		}
	}
}
