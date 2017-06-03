#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long LL;
int N,Q;
int A[1000001],NEXT[1000001];
pair<int,int>DP[1000001];
LL _SUM[1000001];
inline LL Sum(const int id)
{
	if(id<=N)return _SUM[id];
	else if(id<=N*2)return _SUM[N]+_SUM[id-N];
	else if(id<=N*3)return _SUM[N]*2LL+_SUM[id-N*2];
	else assert(0);
	return -1LL;
}
inline void getmin(int &a,const int b){if(b<a)a=b;}
int Solve(const LL d)
{
	for(int l=N,r=2*N;l>=0;l--)
	{
		while(Sum(r)-Sum(l)>d)--r;
		NEXT[l]=r;
		if(r>=N)DP[l]=make_pair(1,r);
		else DP[l]=make_pair(DP[r].first+1,DP[r].second);
	}
	int ans=2147483647;
	for(int start=0;start<=NEXT[0];start++)
	{
		const pair<int,int>&p=DP[start];
		if(p.second<N+start)
		{
//			printf("%d %d\n",NEXT[p.second-N]+N,N+start);
			assert(NEXT[p.second-N]+N>=N+start);
			getmin(ans,p.first+1);
		}
		else getmin(ans,p.first);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		int mx=0;
		for(int i=1;i<=N;i++)scanf("%d",&A[i]),mx=max(mx,A[i]);
		_SUM[0]=0LL;
		for(int i=1;i<=N;i++)_SUM[i]=_SUM[i-1]+A[i];
		for(LL d;Q--;)
		{
			scanf("%lld",&d);
			if(d<mx)puts("NIE");
			else if(d>=_SUM[N])puts("1");
			else printf("%d\n",Solve(d));
		}
	}
	return 0;
}
