#include<cstdio>
#include<cassert>
#include<algorithm>
#define int long long
using namespace std;
const int INF=2147483647;
int N,S[1000000],CNT[1000000];
bool Solve()
{
	if(N==1)return S[0]==0;
	int mn=INF,mx=-INF;
	long long sum=0;
	for(int i=0;i<N;i++)sum+=S[i],mn=min(mn,S[i]),mx=max(mx,S[i]);
	if(mx>=N||mn<=0)return false;
	if(sum%2==1)return false;
	if(sum/2<N-1)return false;
	for(int i=1;i<N;i++)CNT[i]=0;
	for(int i=0;i<N;i++)++CNT[S[i]];
	for(int i=N-2;i>=1;i--)CNT[i]+=CNT[i+1];
	int vertex=0;
	for(int h=N-1;h>=1;h--)
	{
		assert(CNT[h]-vertex>=0);
		while(CNT[h]-vertex)
		{
			++vertex;
			int remain=h;
			for(int i=h;remain&&i>=1;i--)
			{
				const int v=min(remain,CNT[i]-vertex);
				assert(v>=0);
				CNT[i]-=v,remain-=v;
			}
			if(remain)return false;
		}
	}
	return true;
}
main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1&&N!=0)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		puts(Solve()?"Possible":"Not possible");
	}
	return 0;
}
