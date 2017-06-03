#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
int N;
int main()
{
	while(scanf("%d",&N)==1)
	{
		priority_queue<LL,vector<LL>,greater<LL> >pq;
		for(int i=0;i<N;i++)
		{
			static LL v;scanf("%lld",&v);
			pq.push(v);
		}
		LL ans=0LL;
		while(pq.size()>=2)
		{
			LL a=pq.top();pq.pop();
			LL b=pq.top();pq.pop();
			ans+=a+b;
			pq.push(a+b);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
