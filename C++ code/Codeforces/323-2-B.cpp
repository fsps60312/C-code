#include<bits/stdc++.h>
using namespace std;
int N,S[1000];
bool VIS[1000];
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)VIS[i]=false;
		int cnt=0,ans=-1;
		for(int d=1;cnt<N;d^=1)
		{
			ans++;
			if(d)
			{
				for(int i=0;i<N;i++)
				{
					if(VIS[i])continue;
					if(S[i]<=cnt)VIS[i]=true,cnt++;
				}
			}
			else
			{
				for(int i=N-1;i>=0;i--)
				{
					if(VIS[i])continue;
					if(S[i]<=cnt)VIS[i]=true,cnt++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
