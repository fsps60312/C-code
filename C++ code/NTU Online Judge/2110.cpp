#include<cstdio>
#include<cassert>
using namespace std;
int N,A[100000];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)A[i]=i+1-A[i];
		for(int i=0;i<N;i++)printf(" %d",A[i]);puts("");
		static int dp[100000];
		int ans=0;
		for(int i=0;i<N;i++)if(A[i]>=0)
		{
			int l=0,r=ans;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(A[i]>=dp[mid])l=mid+1;
				else r=mid;
			}
			if(r==ans)++ans;
			dp[r]=A[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
