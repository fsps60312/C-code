#include<cstdio>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int K,N,P[100001];
int DP[100002],SUM[100001];
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(_a),b(_b){}
};
struct CmpB
{
	bool operator()(const Pair &a,const Pair &b)const{return a.b>b.b;}
};
struct CmpA
{
	bool operator()(const Pair &a,const Pair &b)const{return a.a>b.a;}
};
int Solve()
{
	if(K==1)
	{
		int ans=0;
		for(int i=1;i<=N;i++)ans+=P[i];
		return ans;
	}
	assert(K==2);
	SUM[0]=0;
	for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+P[i];
	DP[N+1]=0;
	priority_queue<Pair,vector<Pair>,CmpB>pq1;
	priority_queue<Pair,vector<Pair>,CmpA>pq2;
	pq1.push(Pair(P[N]+SUM[N-1],P[N]+DP[N+1]));
	for(int i=N;i>=1;i--)
	{
		while(!pq1.empty())
		{
			const Pair p=pq1.top();
			if(p.a-SUM[i-1]>p.b)pq2.push(pq1.top()),pq1.pop();
			else break;
		}
		DP[i]=min(pq1.empty()?INF:pq1.top().b,pq2.empty()?INF:pq2.top().a-SUM[i-1]);
		if(i>1)pq1.push(Pair(P[i-1]+SUM[i-2],P[i-1]+DP[i]));
//		for(int j=i;j<=N;j++)getmin(DP[i],P[j]+max(SUM[j-1]-SUM[i-1],DP[j+1]));
//		printf("DP[%d]=%d\n",i,DP[i]);
	}
	return DP[1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&N)==2)
	{
		for(int i=1;i<=N;i++)scanf("%d",&P[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
