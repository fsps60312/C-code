#include<bits/stdc++.h>
using namespace std;
int T,N;
int X[1000000],Y[1000000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
		}
		sort(X,X+N),sort(Y,Y+N);
		long long ans=0LL;
		for(int i=0;i<N/2;i++)ans+=X[N-1-i],ans-=X[i],ans+=Y[N-1-i],ans-=Y[i];
		printf("%lld\n",ans);
	}
	return 0;
}
