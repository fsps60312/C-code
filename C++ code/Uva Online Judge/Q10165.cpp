#include<cstdio>
int N,P,SG;
int main()
{
//	int sg[101];sg[0]=0;
//	for(int i=1;i<=100;i++)
//	{
//		int vis[101];for(int j=0;j<=100;j++)vis[j]=0;
//		for(int j=0;j<i;j++)
//	}
	while(scanf("%d",&N)==1&&N)
	{
		SG=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&P);
			SG^=P;
		}
		printf(SG?"Yes\n":"No\n");
	}
	return 0;
}
