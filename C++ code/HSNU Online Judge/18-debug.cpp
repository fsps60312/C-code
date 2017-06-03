#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct Pair
{
	LL guard,cnt;
	bool operator<(const Pair &p)const{return guard>p.guard;}
}A[200002],B[200002];
struct Func
{
	LL height,sum;
	Func(){}
	Func(LL height,LL sum):height(height),sum(sum){}
}F[200002],G[200002];
int N,M;
bool solve()
{
	for(int i=1,j=0;i<=N;i++)
	{
		while(j<M&&G[j+1].height<F[i].height)j++;
		LL width=(G[j+1].sum-G[j].sum)/(G[j+1].height-G[j].height);
		if(G[j].sum+width*(F[i].height-G[j].height)<F[i].sum)return 0;
	}
	return 1;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%lld%lld",&A[i].guard,&A[i].cnt);
		scanf("%d",&M);
		for(int i=1;i<=M;i++)scanf("%lld%lld",&B[i].guard,&B[i].cnt);
		sort(A+1,A+N+1);
		sort(B+1,B+M+1);
		for(int i=1;i<=N;i++)
		{
			//F[i].height:row cnt
			//F[i].sum:guard cnt
			//F[i].height:height(small->large)
			//F[i].sum:psumramid sum from button
			F[i].height=F[i-1].height+A[i].cnt;
			F[i].sum=F[i-1].sum+A[i].guard*A[i].cnt;
		}
		LL sum=0L;
		for(int i=1;i<=M;i++)sum+=B[i].cnt;
		for(int i=1,c=M;i<=M;i++,c--)
		{
			//sum:width(column cnt)
			//G[i].height:height(small->large)
			//G[i].sum:psumramid sum from buttom
			G[i].height=B[c].guard;
			G[i].sum=G[i-1].sum+(B[c].guard-B[c+1].guard)*sum;
			sum-=B[c].cnt;
		}
		if(F[N].height>G[M].height)G[M+1]=Func(F[N].height,G[M].sum),M++;
		if(solve())printf("1\n");
		else printf("0\n");
	}
}
