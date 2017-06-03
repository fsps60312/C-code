#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,S[200000];
int Solve(const int lb,const int rb)
{
	assert((lb+rb)%2==0);
	const int mid=(lb+rb)/2,len=mid-(lb+1)+1;
	int ans=INF;
	for(int l=lb+1,r=mid;r<rb;++l,++r)ans=min(ans,S[r+1]-S[l-1]);
	return ans;
}
int Solve()
{
	if(N==2)return S[1]-S[0];
	else return min(Solve(0,N-2),Solve(1,N-1));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		printf("%d\n",Solve());
	}
	return 0;
}
