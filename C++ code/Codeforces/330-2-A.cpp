#include<cstdio>
int N,M;
int main()
{
	scanf("%d%d",&N,&M);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			ans+=(a|b);
		}
	}
	printf("%d\n",ans);
	return 0;
}
