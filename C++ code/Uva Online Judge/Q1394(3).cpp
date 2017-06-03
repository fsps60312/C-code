#include<cstdio>
#include<cstdlib>
int N,K,M,DP[10001];
int mod(int a,int b){return (a%b+b)%b;}
int main()
{
	while(scanf("%d%d%d",&N,&K,&M)==3&&(N||K||M))
	{
		DP[2]=1;
		for(int i=3;i<=N;i++)
		{
			DP[i]=mod(DP[i-1]-K,i-1)+1;
			//printf("DP[%d]=%d\n",i,DP[i]);
		}
		printf("%d\n",mod((M-1)-DP[N],N)+1);
	}
	return 0;
}
