#include<cstdio>
#include<queue>
using namespace std;
typedef long long LL;
struct Cable
{
	int l,r;
	LL cost;
	Cable(){}
	Cable(const int &l,const int &r,const LL &c):l(l),r(r),cost(c){}
	bool operator<(const Cable &c)const{return cost>c.cost;}
};
int N,K,L[100000],R[100000];
LL DIST[100000],LC[100000],RC[100000],COST[99999];
priority_queue<Cable>PQ;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)scanf("%lld",&DIST[i]);
	for(int i=0;i<N-1;i++)PQ.push(Cable(i,i+1,COST[i]=DIST[i+1]-DIST[i]));
	for(int i=0;i<N;i++)
	{
		L[i]=i-1,R[i]=i+1;
		if(i>0)LC[i]=COST[i-1];
		if(i<N-1)RC[i]=COST[i];
	}
	LL ans=0LL;
	for(int i=0;i<K;i++)
	{
		Cable c=PQ.top();PQ.pop();
		for(;R[c.l]!=c.r||L[c.r]!=c.l;)c=PQ.top(),PQ.pop();
		ans+=c.cost;
		if(c.l==0||c.r==N-1)continue;
		c.cost*=-1LL;
		c.cost+=LC[c.l],c.l=L[c.l];
		c.cost+=RC[c.r],c.r=R[c.r];
		LC[c.r]=RC[c.l]=c.cost;
		R[c.l]=c.r;
		L[c.r]=c.l;
		PQ.push(c);
	}
	printf("%lld\n",ans);
	return 0;
}
