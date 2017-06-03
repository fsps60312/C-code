#include<bits/stdc++.h>
using namespace std;
int T,N;
long long X[1000000],Y[1000000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int l1=0,r1=0,l2=0,r2=0;
		long long v1,v2;
		scanf("%lld%lld",&X[0],&Y[0]);
		v1=X[0],v2=Y[0];
		for(int i=1;i<N;i++)
		{
			scanf("%lld%lld",&X[i],&Y[i]);
			if(X[i]>v1)
			{
				if(r1<=l1)r1++;
				else l1++,v1=X[i];
			}
			else
			{
				if(l1<=r1)l1++;
				else 
			}
			if(Y[i]>v2)
			{
				if(r2<=l2)r2++;
				else l2++,v2=Y[i];
			}
		}
		long long ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(v1-X[i])+abs(v2-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
