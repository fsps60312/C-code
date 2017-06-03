#include<bits/stdc++.h>
using namespace std;
int V,N,DP[10001];
int main()
{
	while(scanf("%d%d",&N,&V)==2)
	{
		for(int i=0;i<=N;i++)DP[i]=0;
		while(V--)
		{
			static int w,v;
			scanf("%d%d",&w,&v);
			for(int i=0;i+v<=N;i++)DP[i+v]=max(DP[i+v],DP[i]+w);
		}
		int ans=0;
		for(int i=0;i<=N;i++)ans=max(ans,DP[i]);
		printf("%d\n",ans);
	}
	return 0;
}
