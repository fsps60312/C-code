#include<cstdio>
int N;
int main()
{
	while(scanf("%d",&N)==1)
	{
		N=N*(N+1)/2;
		puts(N&1?"Alice":"Bob");
		break;
	}
	return 0;
}
