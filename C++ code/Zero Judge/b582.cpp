#include<bits/stdc++.h>
using namespace std;
int T,N;
long long X[1000000],Y[1000000];
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("new.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%lld%lld",&X[i],&Y[i]);
		}
		sort(X,X+N),sort(Y,Y+N);
		long long ans=0LL;
		for(int i=0;i<N/2;i++)ans+=X[N-1-i]-X[i]+Y[N-1-i]-Y[i];
		printf("%lld\n",ans);
	}
	return 0;
}
