#include<cstdio>
#include<queue>
using namespace std;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[2000001];
int A,B;
int main()
{
	while(scanf("%d%d",&A,&B)==2)
	{
		for(int i=0;i<=2000000;i++)VIS[i]=false;
		priority_queue<Pq>pq;
		pq.push(Pq(A,0));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(p.u<0||p.u>2000000||VIS[p.u])continue;
			VIS[p.u]=true;
			if(p.u==B){printf("%d\n",p.cost);break;}
			pq.push(Pq(p.u+1,p.cost+2));
			pq.push(Pq(p.u+2,p.cost+3));
			pq.push(Pq(p.u-1,p.cost+2));
			pq.push(Pq(p.u-2,p.cost+3));
			pq.push(Pq(p.u*2,p.cost+3));
			pq.push(Pq(p.u/2,p.cost+3));
		}
	}
	return 0;
}
