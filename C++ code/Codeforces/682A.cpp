#include<cstdio>
#include<cassert>
using namespace std;
int N,M;
long long CA[5],CB[5];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<5;i++)CA[i]=N/5;
		for(int i=1;i<=N%5;i++)++CA[i];
		for(int i=0;i<5;i++)CB[i]=M/5;
		for(int i=1;i<=M%5;i++)++CB[i];
		long long ans=CA[0]*CB[0];
		for(int i=1;i<5;i++)ans+=CA[i]*CB[5-i];
		printf("%lld\n",ans);
	}
	return 0;
}
