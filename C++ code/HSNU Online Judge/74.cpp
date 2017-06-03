#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
int N;
priority_queue<LL>MX;
priority_queue<LL,vector<LL>,greater<LL> >MN;
int main()
{
	while(scanf("%d",&N)==1)
	{
		while(!MX.empty())MX.pop();
		while(!MN.empty())MN.pop();
		LL ans=0LL;
		for(int i=0,k;i<N;i++)
		{
			scanf("%d",&k);
			while(k--)
			{
				static LL v;scanf("%lld",&v);
				MX.push(v),MN.push(v);
			}
			ans+=MX.top()-MN.top();
			MX.pop(),MN.pop();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
