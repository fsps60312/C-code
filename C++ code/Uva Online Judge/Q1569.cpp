#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
int N,M;
bool VALID[100000],VIS[100000];
struct Pq
{
	LL val,mod;
	int id;
	Pq(){} 
	Pq(const LL _val,const LL _mod,const int _id):val(_val),mod(_mod),id(_id){assert(mod<=100000000000000000LL);}
	bool operator<(const Pq &p)const{return val!=p.val?val>p.val:mod>p.mod;}
};
LL Solve()
{
	priority_queue<Pq>pq;
	for(int i=1;i<10;i++)if(VALID[N*i%10])pq.push(Pq(N*i,10,N*i/10));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.id])continue;
		VIS[p.id]=true;
		if(VALID[p.id])return p.val;
		for(int i=0;i<10;i++)if(VALID[(p.id+(N*i))%10])
		{
			Pq q=p;
			q.val+=q.mod*N*i;
			q.mod*=10LL;
			(q.id+=N*i)/=10;
			pq.push(q);
		}
	}
	return 0LL;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<100000;i++)VALID[i]=VIS[i]=false;
		for(int i=0,v;i<M;i++)scanf("%d",&v),VALID[v]=true;
		for(int i=10;i<100000;i++)
		{
			VALID[i]=true;
			for(int n=i;n;n/=10)if(!VALID[n%10]){VALID[i]=false;break;}
		}
		printf("%lld\n",Solve());
	}
	return 0;
}
