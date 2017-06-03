#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
LL T,A,B,C;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		LL s1;
		scanf("%d%lld%lld%lld%lld",&N,&A,&B,&C,&s1);
		LL mx=s1,sum=s1;
		for(int i=1;i<N;i++)
		{
			s1=(s1*A+B)%C;
			sum+=s1;
			mx=max(mx,s1);
		}
		LL ans=mx*(N-1)+sum-mx;
		printf("%lld\n",ans);
	}
	return 0;
}
