#include<cstdio>
int N,D[10001];
int main()
{
	while(scanf("%d",&N)==1)
	{
		int n=0,ans=0;
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			while(n<b)D[++n]=0;
			if(a>D[b])
			{
				ans+=a-D[b];
				D[b]=a;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
