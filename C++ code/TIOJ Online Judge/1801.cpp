#include<cstdio>
int M,N,K,DP[100001];
int mod(int a,int b){return (a%b+b)%b;}
int main()
{
	int kase=1;
	scanf("%d",&M);
	while(M--)
	{
		scanf("%d%d",&N,&K);
		DP[1]=0;
		for(int i=2;i<=N;i++)
		{
			//(DP[i]+K)%(i-1)=DP[i-1]
			DP[i]=mod(DP[i-1]-K,i-1);
			//if(DP[i]==DP[i-1])
			DP[i]++;
			//printf("DP[%d]=%d\n",i,DP[i]);
		}
		printf("Case %d: %d\n",kase++,mod(N-mod(DP[N]-(K-1),N),N)+1);
	}
	return 0;
}
