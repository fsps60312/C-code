#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
//const int INF=2147483647;
int N,P,G[100][100];
main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%lld",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld",&N,&P);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%lld",&G[i][j]);
		static int sum[100];
		for(int i=0;i<N;i++)sum[i]=0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)sum[i]+=G[i][j],sum[j]+=G[i][j];
		sort(sum,sum+N);
		int ans=0;
		for(int j=0;j<N;j++)
		{
			const int i=N-1-j;
			if(j&1)ans-=sum[i];
			else ans+=sum[i];
		}
		printf("%lld\n",P==1?ans/2:-ans/2);
	}
	return 0;
}
