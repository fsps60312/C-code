#include<cstdio>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
struct FuelStop
{
	int dist,fuel;
	bool operator<(const FuelStop &f)const{return dist<f.dist;}
}STOP[10000];
int N,L,P;
int Solve()
{
	priority_queue<int>pq;
	int ans=0,dist=P,cur=0;
	while(dist<L)
	{
		while(cur<N&&STOP[cur].dist<=dist)pq.push(STOP[cur++].fuel);
		if(pq.empty())return -1;
		dist+=pq.top(),ans++,pq.pop();
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&STOP[i].dist,&STOP[i].fuel);
		scanf("%d%d",&L,&P);
		for(int i=0;i<N;i++)STOP[i].dist=L-STOP[i].dist;
		sort(STOP,STOP+N);
		printf("%d\n",Solve());
	}
	return 0;
}
