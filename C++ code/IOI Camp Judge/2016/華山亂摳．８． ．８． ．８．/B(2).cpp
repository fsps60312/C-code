#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M,A,B,ANS[100000];
set<int>ET[100000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	set<int>remain;for(int i=0;i<N;i++)remain.insert(i);
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.cost>=ANS[p.u])continue;
		ANS[p.u]=p.cost;
		vector<int>to_erase;
		for(const int v:remain)if(v!=p.u&&ET[p.u].find(v)==ET[p.u].end())
		{
			if(ANS[p.u]+B<ANS[v])
			{
				pq.push(Pq(v,ANS[p.u]+B));
			}
			to_erase.push_back(v);
		}
		for(const int v:to_erase)remain.erase(v);
		for(const int nxt:ET[p.u])pq.push(Pq(nxt,p.cost+A));
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
			if(a==b)continue;
			ET[a].insert(b),ET[b].insert(a);
		}
		Solve();
		printf("%d",ANS[0]);
		for(int i=1;i<N;i++)printf(" %d",ANS[i]);puts("");
	}
	return 0;
}
