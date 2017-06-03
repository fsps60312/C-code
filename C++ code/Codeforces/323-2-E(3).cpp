#include<bits/stdc++.h>
using namespace std;
int N,S[200000],CNT[200000];
bool VIS[200000];
int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	long long ans=0LL;
	for(int g=1;g<N;g++)
	{
		if(N%g!=0)continue;
		bool all=true;
		for(int i=0;i<g;i++)
		{
			int mx=0;
			for(int j=i;j<N;j+=g)mx=max(mx,S[j]);
			for(int j=i;j<N;j+=g)all&=(VIS[j]=(S[j]>=mx));
		}
		if(all){for(int i=1;i<N;i++)if(gcd(i,N)==g)ans+=N;}
		else
		{
			for(int i=1;i<N;i++)CNT[i]=0;
			for(int i=0,j=0;i<N;)
			{
				if(!VIS[i])
				{
					i++,j=i;
					continue;
				}
				while(VIS[(++j)%N]);
				for(int k=i;k<N&&k<j;k++)CNT[j-k]++;
//				printf("i=%d,l=%d\n",i,l);
				i=j;
			}
			for(int i=N-2;i>=1;i--)CNT[i]+=CNT[i+1];
			for(int i=1;i<N;i++)if(gcd(i,N)==g)ans+=CNT[i];
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
