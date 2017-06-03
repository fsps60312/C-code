#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int K,N,P[100000];
int Solve()
{
	if(K==1)
	{
		int ans=0;
		for(int i=0;i<N;i++)ans+=P[i];
		return ans;
	}
	assert(K==2);
	static int left[100001],right[100001];
	left[0]=0;
	for(int i=0;i<N;i++)left[i+1]=left[i]+P[i];
	right[N]=0;
	for(int i=N-1;i>=0;i--)right[i]=right[i+1]+P[i];
	int ans=2147483647;
	for(int i=0;i<=N;i++)if(max(left[i],right[i])<ans)ans=max(left[i],right[i]);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&N)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&P[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
