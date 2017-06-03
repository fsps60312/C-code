#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int K,N,P[100001];
int DP[100002],SUM[100001];
int GetDP(const int i)
{
	int &dp=DP[i];
	if(dp!=-1)return dp;
	dp=INF;
	for(int r=i;r<=N;r++)getmin(dp,P[r]+max(SUM[r-1]-SUM[i-1],GetDP(r+1)));
	return dp;
}
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
	for(int i=1;i<=N;i++)DP[i]=-1,SUM[i]=SUM[i-1]+P[i];
	DP[N+1]=0;
	return GetDP(1);
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
