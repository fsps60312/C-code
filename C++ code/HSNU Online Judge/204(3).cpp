#include<bits/stdc++.h>
using namespace std;
int N,M[20],DP[1<<20];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&M[i]);
		for(int s=0;s<(1<<N);s++)
		{
			int &dp=DP[s]=0;
			for(int i=0;i<N;i++)if(s&(1<<i))dp+=M[i];
		}
		int ans=0;
		for(int s=0;s<(1<<N);s++)
		{
			for(int a=(s-1)&s,b;a;a=(--a)&s)
			{
				b=s^a;
				if(DP[a]==DP[b])ans++;
			}
		}
		printf("%d\n",ans>>1);
		break;
	}
	return 0;
}
