#include<cstdio>
#include<cstdlib>
int N,M,K,DP[10001];
int mod(int a,int b){return (a%b+b)%b;}
int main()
{
	while(scanf("%d%d%d",&N,&K,&M)==3&&(N||K||M))
	{
		DP[1]=0;
		for(int n=2;n<=N;n++)
		{
			DP[n]=(DP[n-1]+K)%n;
		}
		printf("%d\n",(DP[N]+M)%N+1);
	}
	return 0;
}
