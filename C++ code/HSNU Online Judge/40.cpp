#include<bits/stdc++.h>
using namespace std;
int V,N;
long long DP[10001];
int main()
{
	while(scanf("%d%d",&V,&N)==2)
	{
		for(int i=1;i<=N;i++)DP[i]=0L;
		DP[0]=1L;
		while(V--)
		{
			static int v;
			scanf("%d",&v);
			for(int i=0;i+v<=N;i++)DP[i+v]+=DP[i];
		}
		printf("%lld\n",DP[N]);
	}
	return 0;
}
