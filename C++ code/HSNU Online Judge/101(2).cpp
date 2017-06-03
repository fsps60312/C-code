#include<cstdio>
#include<cassert>
#include<set>
#include<queue>
using namespace std;
int N,L;
set<int>ET[1000000];
struct Route
{
	int now,cost;
	Route(){}
	Route(const int _n,const int _c):now(_n),cost(_c){}
	bool operator<(const Route &r)const{return cost>r.cost;}
};
int Solve()
{
	if(L==0)return 0;
	priority_queue<Route>pq;
	for(int i=0;i<N;i++)if((int)ET[i].size()==1)pq.push(Route(i,1));
	int cnt=(int)pq.size()-L*2;
	int ans=N;
	while(!pq.empty()&&cnt>0)
	{
		const Route r=pq.top();pq.pop();
		assert((int)ET[r.now].size()==1);
		const int nxt=*ET[r.now].begin();
		if((int)ET[nxt].size()==2)pq.push(Route(nxt,r.cost+1));
		else ans-=r.cost,cnt--;
		ET[nxt].erase(r.now);
		ET[r.now].erase(nxt);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&L);
	for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].insert(b),ET[b].insert(a);
	printf("%d\n",Solve());
	return 0;
}
/*
*/
