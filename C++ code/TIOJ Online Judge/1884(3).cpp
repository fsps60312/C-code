#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int N,K,L,S[10000001];
LL LEFT[10000001],RIGHT[10000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&K,&L);
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&S[i]);
			if(S[i]==0)i--,N--;
		}
		LEFT[0]=RIGHT[0]=0LL;
		for(int i=1;i<=N;i++)
		{
			LEFT[i]=LEFT[max(0,i-K)]+2LL*S[i];
			RIGHT[i]=RIGHT[max(0,i-K)]+2LL*(L-S[N+1-i]);
		}
		LL ans=RIGHT[N];
		for(int i=1;i<=N;i++)getmin(ans,LEFT[i]+RIGHT[N-i]);
		for(int i=1;i+K-1<=N;i++)getmin(ans,LEFT[i-1]+L+RIGHT[N+1-(i+K)]);
		printf("%lld\n",ans);
	}
	return 0;
}
