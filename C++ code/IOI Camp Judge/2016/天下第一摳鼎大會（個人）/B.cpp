#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[1000],DP[1000],PRE[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int len=0;
		for(int i=0;i<N;i++)
		{
			int l=0,r=len;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(S[i]<=S[DP[mid]])r=mid;
				else l=mid+1;
			}
			PRE[i]=r?DP[r-1]:-1;
			DP[r]=i;
			if(r==len)len++;
		}
		printf("%d\n",len);
		vector<int>ans;
		for(int i=0,u=DP[len-1];i<len;i++,u=PRE[u])ans.push_back(S[u]);
		for(int i=len-1;i>=0;i--)
		{
			if(i<len-1)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
