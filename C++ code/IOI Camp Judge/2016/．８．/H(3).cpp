#include<cstdio>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,P[3001];
int VIS[3001][3001],KASE=0;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int Solve()
{
	KASE++;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		const int a=p.u/10000,b=p.u%10000;
		if(VIS[a][b]==KASE)continue;
		VIS[a][b]=KASE;
		if(b==N)return p.cost;
		pq.push(Pq(b*10000+(b+1),p.cost+abs(P[b+1]-P[b])));
		pq.push(Pq(a*10000+(b+1),p.cost+abs(P[b+1]-P[a])));
	}
	assert(0);return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int i=0;i<=3000;i++)for(int j=0;j<=3000;j++)VIS[i][j]=0;
	while(testcount--)
	{
		scanf("%d",&N);
		P[0]=0;
		for(int i=1;i<=N;i++)scanf("%d",&P[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
