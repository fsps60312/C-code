#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int K,N,P[100001];
int DP[100002],SUM[100001];
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
	for(int i=N;i>=1;i--)
	{
		DP[i]=INF;
		for(int j=i;j<=N;j++)getmin(DP[i],P[j]+max(SUM[j-1]-SUM[i-1],DP[j+1]));
		printf("DP[%d]=%d\n",i,DP[i]);
	}
	return DP[1];
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&N)==2)
	{
		for(int i=1;i<=N;i++)scanf("%d",&P[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
