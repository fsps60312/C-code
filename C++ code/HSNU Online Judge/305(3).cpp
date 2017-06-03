#include<cstdio>
#include<queue>
using namespace std;
const int INF=2147483647;
const int MAXN=1500001;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[MAXN+1];
int DIST[MAXN+1];
int A,B;
int main()
{
	while(scanf("%d%d",&A,&B)==2)
	{
		for(int i=0;i<=MAXN;i++)VIS[i]=false,DIST[i]=INF;
		priority_queue<Pq>pq;
		pq.push(Pq(A,0));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(p.u<0||p.u>MAXN||VIS[p.u])continue;
			VIS[p.u]=true;
			if(p.u==B){printf("%d\n",p.cost);break;}
			int *nxt=new int[6]{p.u+1,p.u+2,p.u-1,p.u-2,p.u*2,p.u/2};
			int *cost=new int[6]{p.cost+2,p.cost+3,p.cost+2,p.cost+3,p.cost+3,p.cost+3};
			for(int i=0;i<6;i++)if(0<=nxt[i]&&nxt[i]<=MAXN&&cost[i]<DIST[nxt[i]])
			{
				DIST[nxt[i]]=cost[i];
				pq.push(Pq(nxt[i],cost[i]));
			}
		}
	}
	return 0;
}
