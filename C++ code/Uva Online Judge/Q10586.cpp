#include<cstdio>
int N,K,C[10001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)&&!(N==-1&&K==-1))
	{
		for(int i=0;i<=N;i++)scanf("%d",&C[i]);
		if(K<=N)for(int i=N;i>=K;i--)C[i-K]-=C[i],C[i]=0;
		while(!C[N]&&N>0)N--;
		for(K=0;K<=N;K++)
		{
			if(K)printf(" ");
			printf("%d",C[K]);
		}
		printf("\n");
	}
	return 0;
}
