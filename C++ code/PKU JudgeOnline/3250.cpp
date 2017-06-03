#include<cstdio>
#include<cassert>
#include<stack>
using namespace std;
const int INF=2147483647;
typedef long long LL;
int N,S[80001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		S[N]=INF;
		stack<int>stk;stk.push(N);
		LL ans=0LL;
		for(int i=N-1;i>=0;i--)
		{
			while(S[stk.top()]<S[i])stk.pop();
			ans+=stk.top()-i-1;
			stk.push(i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
