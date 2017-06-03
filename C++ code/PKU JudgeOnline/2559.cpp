#include<cstdio>
#include<cassert>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
LL S[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		if(N==0)break;
		for(int i=1;i<=N;i++)scanf("%lld",&S[i]);
		S[0]=-1;
		LL ans=0LL;
		for(int stage=0;stage<=1;stage++)
		{
			stack<LL>stk;
			stk.push(0LL);
			for(int i=1;i<=N;i++)
			{
				while(S[stk.top()]>=S[i])stk.pop();
				LL ta=S[i]*(i-stk.top());
//				printf("i=%d,ta=%lld\n",i,ta);
				if(ta>ans)ans=ta;
				stk.push(i);
			}
			if(stage==0)for(int l=1,r=N;l<r;l++,r--)swap(S[l],S[r]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
