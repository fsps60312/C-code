#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
int N,M;
vector<int>ET[100000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int A,B,DIST[100000];
bool VIS[100000];
void Solve()
{
	for(int i=0;i<N;i++)DIST[i]=B,VIS[i]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.cost>=B)break;
		if(VIS[p.u])continue;
		VIS[p.u]=true,DIST[p.u]=p.cost;
		for(const int nxt:ET[p.u])
		{
			pq.push(Pq(nxt,p.cost+A));
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d%d",&N,&M,&A,&B);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		Solve();
		printf("0");
		for(int i=1;i<N;i++)printf(" %d",DIST[i]);puts("");
	}
	return 0;
}
