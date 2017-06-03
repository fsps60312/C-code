#include "grader.h"
#include<vector>
#include<cassert>
#include<utility>
#include<queue>
#include<cstdio>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Pq
{
	int U;
	LL DIST;
	Pq(){}
	Pq(const int _U,const LL _DIST):U(_U),DIST(_DIST){}
};
bool operator<(const Pq &a,const Pq &b){return a.DIST>b.DIST;}
vector<pair<int,int> >ET[100000];
LL DIST[100000];
int VIS[100000];
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<M;i++)
	{
		const int a=R[i][0],b=R[i][1],c=L[i];
		ET[a].push_back(make_pair(b,c));
		ET[b].push_back(make_pair(a,c));
	}
	for(int i=0;i<N;i++)VIS[i]=0;
	priority_queue<Pq>pq;
	for(int i=0;i<K;i++)++VIS[P[i]],pq.push(Pq(P[i],0));
	assert(!pq.empty());
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		switch(VIS[p.U])
		{
			case 0:++VIS[p.U];break;
			case 1:
			{
//				printf("DIST[%d]=%lld\n",p.U,p.DIST);
				++VIS[p.U];
				DIST[p.U]=p.DIST;
				for(const auto &nxt:ET[p.U])pq.push(Pq(nxt.first,p.DIST+nxt.second));
			}break;
			default:
			{
				assert(VIS[p.U]==2);
			}break;
		}
	}
	assert(VIS[0]==2);
	return (int)DIST[0];
}


