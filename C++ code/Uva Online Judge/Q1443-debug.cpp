#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
int W[40005],SUM[40005];
int DP[40005][2],N,M,D;
int Check(int x)
{
	DP[0][0]=0;
	DP[0][1]=INF;
	for (int i=2;i<=N;i+=2)
	{
		DP[i][0]=INF;
		DP[i][1]=INF;
		for (int len=1;len<=d&&2*len<=i;len++)
		{
			if (SUM[i]-SUM[i-len]>x)break;
			if (SUM[i-len]-SUM[i-2*len]<=x)
			{
				DP[i][0]=min(DP[i][0],DP[i-2*len][1]+1);
				DP[i][1]=min(DP[i][1],DP[i-2*len][0]+1);
			}
		}
	}
	return DP[N][(M-1)%2]<=M-1;
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&D);
		SUM[0]=0;
		for (int i=1;i<=N;i++)
		{
			scanf("%d",&W[i]);
			SUM[i]=SUM[i-1]+W[i];
		}
		if((N&1)||(N<2*(M-1))||(N>2*D*(M-1)))printf("BAD\n");
		else
		{
			int l=1,r=SUM[N];
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(Check(mid))r=mid;
				else l=mid+1;
			}
			printf("%d\n",l);
		}
	}
	return 0;
}
