#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
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
		for(int i=0,now=0,k;i<N;i++)
		{
			scanf("%d",&k);now+=k;
			while(k--)
			{
				static LL v,u;scanf("%lld",&v);u=v;
				MX.push(v);MN.push(u);
			}
			now-=2;
			assert(now>=0);
			ans+=MX.top()-MN.top();
//			printf("(%lld,%lld)\n",MX.top(),MN.top());
			MX.pop();MN.pop();
		}
		printf("%lld\n",ans);
		break;
	}
	return 0;
}
