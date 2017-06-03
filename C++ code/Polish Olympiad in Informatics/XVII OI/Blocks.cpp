#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,M,S[1000000];
LL SUM[1000001];
int Solve(const int len)
{
	SUM[0]=0LL;
	for(int i=0;i<N;i++)SUM[i+1]=SUM[i]+S[i]-len;
	static LL mn[1000001],mx[1000001];
	mn[0]=SUM[0];
	for(int i=1;i<=N;i++)mn[i]=min(mn[i-1],SUM[i]);
	mx[N]=SUM[N];
	for(int i=N-1;i>=0;i--)mx[i]=max(mx[i+1],SUM[i]);
	int ans=0;
	for(int i=0,j=0;i<=N;i++)
	{
		if(j<i)j=i;
		while(j+1<=N&&mx[j+1]>=mn[i])++j;
		ans=max(ans,j-i);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0,v;i<M;i++)
		{
			scanf("%d",&v);
			if(i)putchar(' ');
			printf("%d",Solve(v));
		}
		puts("");
	}
	return 0;
}
