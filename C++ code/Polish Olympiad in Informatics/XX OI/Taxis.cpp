#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
LL M,D,X[500000];
int N;
int Solve()
{
	int ans=0;
	const int least=lower_bound(X,X+N,M-D)-X;
	if(least==N)return false;
	else if(least>=D+M)return 1;
	LL x=0LL;
	for(int i=N-1;i>least&&x<D&&X[i]>D-x;i--)
	{
		x+=X[i]-(D-x);
		ans++;
		if(x>=M)return ans;
	}
	for(int i=least-1;i>=0&&x<D&&X[i]>D-x;i--)
	{
		x+=X[i]-(D-x);
		ans++;
		if(x>=M)return ans;
	}
	if(x>=D)return ans+1;
	if(X[least]<(D-x)+(M-x))return 0;
	else return ans+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%d",&M,&D,&N)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld",&X[i]);
		sort(X,X+N);
		printf("%d\n",Solve());
	}
	return 0;
}
