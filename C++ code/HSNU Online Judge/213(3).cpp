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
		LL mx=s1,sum=s1,s2=s1;
		for(int i=1;i<N;i++)
		{
			s2=(s2*A+B)%C,s2=(s2*A+B)%C;
			s1=(s1*A+B)%C;
			sum+=s1;
			mx=max(mx,s1);
			if(s1==s2)
			{
				LL tsum=0LL,tmx=0LL;
				int cnt=0;
				for(LL j=s1;;)
				{
					j=(j*A+B)%C,cnt++;
					tsum+=j,tmx=max(tmx,j);
//					printf(" %lld",j);
					if(j==s1)break;
				}
//				puts("");
				int n=(N-1-i)/cnt;
//				printf("i=%d,n=%d,cnt=%d\n",i,n,cnt);
//				printf("%lld %lld\n",sum,mx);
				if(n>0)
				{
					i+=cnt*n,sum+=tsum*n,mx=max(mx,tmx);
					if(i>=N)break;
				}
			}
		}
//		printf("%d %lld %lld\n",N,sum,mx);
		LL ans=mx*(N-1)+sum-mx;
		printf("%lld\n",ans);
	}
	return 0;
}
