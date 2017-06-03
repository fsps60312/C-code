#include<cstdio>
#include<cassert>
#include<queue>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,P;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(2,"%d%d",&N,&P);
		long long sum=0LL;
		queue<int>q;
		q.push(sum);
		long long ans=0LL;
		for(int i=0,v;i<N;i++)
		{
			scanf(1,"%d",&v);
			q.push(sum+=v);
			while(q.front()<sum-P)q.pop();
//			printf("sz=%d\n",(int)q.size());
			ans+=(long long)q.size()-1LL;
		}
		static int kase=1;
		printf("Case #%d: %lld\n",kase++,ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
