#include<bits/stdc++.h>
using namespace std;
const int INF=2147483646;
int T,N,M,D;
int W[40001],SUM[40001],DP[40001];
bool Check(int mxw)
{
	DP[0]=0;
	for(int i=2;i<=N;i+=2)
	{
		DP[i]=INF;
		for(int j=1;j<=D&&i-j*2>=0&&SUM[i]-SUM[i-j]<=mxw;j++)
		{
			if(SUM[i-j]-SUM[i-j*2]>mxw)continue;
			DP[i]=min(DP[i],DP[i-j*2]+1);
		}
		printf("mxw=%d,DP[%d]=%d\n",mxw,i,DP[i]);
	}
	return DP[N]<=M-1;
}
int Solve()
{
	if(N&1)return -1;
	if((M-1)*2>N)return -1;
	if((M-1)*2*D<N)return -1;
	int l=1,r=SUM[N],mid;
	while(l<r)
	{
		mid=(l+r)/2;
		printf("(%d,%d)\n",l,r);
		if(Check(mid))r=mid;
		else l=mid+1;
	}
	return l;
}
int main()
{
	freopen("in.txt","r",stdin);
	SUM[0]=0;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&N,&M,&D);
			for(int i=1;i<=N;i++)
			{
				scanf("%d",&W[i]);
				SUM[i]=SUM[i-1]+W[i];
			}
			int ans=Solve();
			if(ans==-1)puts("BAD");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
