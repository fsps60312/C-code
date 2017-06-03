#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
int N;
int main()
{
	scanf(1,"%d",&N);
	priority_queue<int,vector<int>,greater<int> >pq;
	LL ans=0LL;
	for(int i=0,cow;i<N;i++)
	{
		scanf(1,"%d",&cow);
		ans+=(LL)pq.size();
		while(!pq.empty()&&pq.top()<=cow)pq.pop();
		pq.push(cow);
	}
	printf("%lld\n",ans);
	return 0;
}
