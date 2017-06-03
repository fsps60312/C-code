#include<cstdio>
#include<queue>
using namespace std;
typedef long long LL;
int N,K;
LL DIST[100000],COST[99999],LC[100000],RC[100000],L[100000],R[100000];
struct Cable
{
	int l,r;
	LL cost;
	Cable(){}
	Cable(const int &l,const int &r,const LL &c):l(l),r(r),cost(c){}
	bool operator<(const Cable &a)const{return cost>a.cost;}
};
priority_queue<Cable>PQ;
int main()
{
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)scanf("%d",&DIST[i]);
	for(int i=0;i<N-1;i++)
	{
		COST[i]=DIST[i+1]-DIST[i];
		PQ.push(Cable(i,i+1,COST[i]));
	}
	for(int i=0;i<N;i++)
	{
		L[i]=R[i]=i;
		if(i>0)LC[i]=COST[i-1];
		if(i<N-1)RC[i]=COST[i];
	}
	LL ans=0LL;
	for(int i=0;i<K;i++)
	{
		Cable c=PQ.top();PQ.pop();
		for(;L[c.l]!=c.l||R[c.r]!=c.r;)c=PQ.top(),PQ.pop();
		L[c.r]=c.l,R[c.l]=c.r;
		LC[c.r]=c.cost,RC[c.l]=c.cost;
		ans+=c.cost;
		
		LL cost=-c.cost;
		int l=c.l-1,r=c.r+1;
		while(l>=0&&L[l]!=l)
		{
			cost+=RC[l]-RC[L[l]];
			l=L[l]-1;
		}
		while(r<N&&R[r]!=r)
		{
			cost+=LC[r]-LC[R[r]];
			r=R[r]+1;
		}
		if(l<0||r>=N)continue;
		cost+=RC[l]+LC[r];
		PQ.push(Cable(l,r,cost));
	}
	printf("%d\n",ans);
	return 0;
}
