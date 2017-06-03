#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
LL T,N,A,B,C,S[1000000];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		LL s1;
		scanf("%lld%lld%lld%lld%lld",&N,&A,&B,&C,&s1);
		assert(N%2LL==1LL);
		S[0]=s1;
		for(LL i=1LL;i<N;i++)S[i]=(S[i-1LL]*A+B)%C;
		for(int i=0;i<N;i++)printf(" %lld",S[i]);puts("");
		sort(S,S+N);
		LL ans=0LL;
		for(LL i=0LL;i<=N/2LL;i++)ans+=S[i];
		if(N>1LL)ans+=S[N/2LL+1LL]*2LL;
		for(LL i=N/2LL+2LL;i<N;i++)ans+=S[i]*3LL;
		printf("%lld\n",ans);
	}
	return 0;
}
