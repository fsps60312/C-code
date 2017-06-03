#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,VAL[1000001];
LL DP[1000001];
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		DP[N]=0LL,VAL[N]=0;
		LL sum=0LL;
		int ans=0;
		for(int i=1,l=N;i<=N;i++)
		{
			if(true){static LL v;scanf("%lld",&v),sum+=v;}
			const int idx=upper_bound(DP+l,DP+N+1,sum)-DP;
			if(idx>l&&ans<i-VAL[idx-1])ans=i-VAL[idx-1];
			if(sum<DP[l])DP[--l]=sum,VAL[l]=i;
			for(int j=l;j<=N;j++)printf("(%lld,%d)",DP[j],VAL[j]);puts("");
		}
		printf("%d\n",ans);
	}
	return 0;
}
