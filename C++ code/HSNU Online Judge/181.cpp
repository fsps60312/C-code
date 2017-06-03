#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long LL;
LL Sq(const LL &v){return v*v;}
struct Zombie
{
	LL x,y,v;
	bool operator<(const Zombie &z)const{return x<z.x;}
}Z[1000002];
int N,LEFT[1000001],RIGHT[1000001];
LL SUM[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%lld%lld%lld",&Z[i].x,&Z[i].y,&Z[i].v),Z[i].x=Sq(Z[i].x)+Sq(Z[i].y);
	sort(Z+1,Z+N+1);
	if(true)
	{
		Z[0].x=-1;
		int j=0;
		for(int i=1;i<=N;i++)
		{
			if(Z[i].x==Z[i-1].x)Z[j].y+=Z[i].y,Z[j].v=min(Z[j].v,Z[i].v);
			else Z[++j]=Z[i];
		}
		N=j;
	}
	for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+Z[i].y;
	Z[0].v=Z[N+1].v=-1;
	if(true)
	{
		stack<int>stk;
		stk.push(0);
		for(int i=1;i<=N;i++)
		{
			while(Z[stk.top()].v>Z[i].v)stk.pop();
			LEFT[i]=stk.top();
			stk.push(i);
		}
	}
	if(true)
	{
		stack<int>stk;
		stk.push(N+1);
		for(int i=N;i>=1;i--)
		{
			while(Z[stk.top()].v>Z[i].v)stk.pop();
			RIGHT[i]=stk.top();
			stk.push(i);
		}
	}
	LL ans=0LL;
	for(int i=1;i<=N;i++)ans=max(ans,Z[i].v*(SUM[RIGHT[i]-1]-SUM[LEFT[i]]));
	printf("%lld\n",ans);
	return 0;
}
