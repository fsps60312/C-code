#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,T[1000001],W[1000001],A[1000001],B[1000001];
struct Bit
{
	int v[1000001];
	void Clear(){for(int i=1;i<=N;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i){while(i<=N){v[i]++;i+=lowbit(i);}}
	int Query(int i){int ans=0;while(i){ans+=v[i];i-=lowbit(i);}return ans;}
}BIT;
LL Solve()
{
	BIT.Clear();
	LL ans=0L;
	for(int i=1;i<=N;i++)
	{
		int &a=A[i];
		ans+=W[i]*(i-1-BIT.Query(a));
printf("%d add:%d*%d\n",i,W[i],i-1-BIT.Query(a));
		BIT.Add(a);
	}
	BIT.Clear();
	for(int i=N;i>=1;i--)
	{
		int &a=A[i];
		ans+=W[i]*(BIT.Query(a-1));
printf("%d add:%d*%d\n",i,W[i],BIT.Query(a-1));
		BIT.Add(a);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&W[i]);
		for(int i=1;i<=N;i++)scanf("%d",&A[i]);
		for(int i=1,v;i<=N;i++){scanf("%d",&v);B[v]=i;}
		for(int i=1;i<=N;i++)A[i]=B[A[i]],T[B[i]]=W[i];
		for(int i=1;i<=N;i++)W[i]=T[A[i]];
for(int i=1;i<=N;i++)printf(" %d",A[i]);puts("");
for(int i=1;i<=N;i++)printf(" %d",W[i]);puts("");
		printf("%lld\n",Solve());
	}
	return 0;
}
