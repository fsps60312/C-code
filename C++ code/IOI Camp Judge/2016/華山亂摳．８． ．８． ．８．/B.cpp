#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int INF=2147483647;
int N,M,A,B,ANS[100000];
set<int>ET[100000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[100000];
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=INF,VIS[i]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.u])continue;
		VIS[p.u]=true;
		if(p.cost>=ANS[p.u])break;
		ANS[p.u]=p.cost;
		for(const int nxt:ET[p.u])pq.push(Pq(nxt,p.cost+A));
	}
	int ans=-1,mindist=INF;
	for(int i=0;i<N;i++)if((int)ET[i].size()<N-1&&ANS[i]<mindist)ans=i,mindist=ANS[i];
	if(ans!=-1)
	{
		for(int i=0;i<N;i++)if(ANS[i]>=mindist+B)ANS[i]=mindist+B;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
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
