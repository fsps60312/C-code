#include<cstdio>
#include<cassert>
#include<stack>
using namespace std;
typedef long long LL;
int N;
LL S[100002];
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		scanf("%d",&N);
		if(N==0)break;
		for(int i=1;i<=N;i++)scanf("%lld",&S[i]);
		S[0]=S[N+1]=-1LL;
		static int left[100001];
		stack<int>stk;stk.push(0);
		for(int i=1;i<=N;i++)
		{
			while(S[stk.top()]>=S[i])stk.pop();
			left[i]=stk.top();
			stk.push(i);
		}
		while(!stk.empty())stk.pop();stk.push(N+1);
		LL ans=0LL;
		for(int i=N;i>=1;i--)
		{
			while(S[stk.top()]>=S[i])stk.pop();
			const LL &ta=S[i]*(stk.top()-left[i]-1);
			if(ta>ans)ans=ta;
			stk.push(i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
