#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
//#include<stack>
using namespace std;
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
int N,REQUIRE[24],WORKER[24];
struct Edge
{
	const int u,cost;
	Edge(const int _u=0,const int _c=0):u(_u),cost(_c){}
};
vector<Edge>ET[33];
bool NegaCycle()
{
	static int dist[33],counter[33];
	static bool inq[33];
	for(int i=0;i<=32;i++)dist[i]=counter[i]=0,inq[i]=true;
	queue<int>q;
	for(int i=0;i<=32;i++)q.push(i);
//	stack<int>stk;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
//		stk.push(u);
//		printf("u=%d,dist=%d\n",u,dist[u]);
		inq[u]=false;
		for(const Edge &e:ET[u])if(dist[u]+e.cost<dist[e.u])
		{
//			stk.push(u),stk.push(e.u);
			dist[e.u]=dist[u]+e.cost;
			if(counter[e.u]++>2*33)
			{
//				printf("cycle:");
//				for(int i=0;i<100;i++)
//				{
//					int a=stk.top();stk.pop();
//					printf("(%d,%d)",a,stk.top()),stk.pop();
//				}puts("");
				return true;
			}
			if(!inq[e.u])q.push(e.u),inq[e.u]=true;
		}
	}
	return false;
}
bool Solve(const int worker)
{
	for(int i=0;i<=32;i++)ET[i].clear();
	for(int i=0;i<8;i++)ET[i].push_back(Edge(i+24,worker));//sum[24+i+1]-sum[i]<=worker,sum[i]+worker>=sum[24+i+1]
	for(int i=0;i<32;i++)ET[i].push_back(Edge(i+1,WORKER[i%24]));//sum[i+1]-sum[i]<=w,sum[i]+w>=sum[i+1]
	for(int i=0;i<24;i++)ET[i+7+1].push_back(Edge(i,-REQUIRE[(i+7)%24]));//sum[i+7+1]-sum[i]>=R[i+7],sum[i+7+1]-R[i+7]>=sum[i]
//	for(int i=0;i<=32;i++)
//	{
//		printf("from %d: ",i);for(const Edge &e:ET[i])printf("(%d,%d)",e.u,e.cost);puts("");
//	}
	return !NegaCycle();
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<24;i++)scanf(1,"%d",&REQUIRE[i]);
	for(int i=0;i<24;i++)WORKER[i]=0;
	scanf(1,"%d",&N);
	for(int i=0,v;i<N;i++)scanf(1,"%d",&v),WORKER[v]++;
	int l=0,r=N+1;
	while(l<r)
	{
		const int mid=(l+r)/2;
//		printf("(%d,%d)\n",l,r);
		if(Solve(mid))r=mid;
		else l=mid+1;
	}
//	for(int i=0;i<24;i++)printf("(%d,%d)",REQUIRE[i],WORKER[i]);puts("");
	if(r==N+1)puts("No Solution");
	else printf("%d\n",r);
	return 0;
}
