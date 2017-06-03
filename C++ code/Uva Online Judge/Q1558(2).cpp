#include<cstdio>
#include<cassert>
using namespace std;
int T,N;
int DP[1<<21];
inline int Choose(const int s,const int v)
{
	assert(s&(1<<v));
	int ts=s;
	for(int i=0;i<=20;i++)if(i!=1&&!(s&(1<<i)))
	{
		for(int cnt=1;i+v*cnt<=20;cnt++)ts&=~(1<<(i+v*cnt));
	}
	return ts;
}
int Win(const int s)
{
	int &dp=DP[s];
	if(dp!=-1)return dp;
	for(int i=2;i<=20;i++)if((s&(1<<i)))
	{
		if(Win(Choose(s,i))==0)return dp=1;
	}
	return dp=0;
}
int main()
{
	scanf("%d",&T);
	for(int i=0;i<(1<<21);i++)DP[i]=-1;
	while(T--)
	{
		scanf("%d",&N);
		int s=0;
		for(int i=0,v;i<N;i++)scanf("%d",&v),s|=(1<<v),assert(v>=2&&v<=20);
		static int kase=1;
		printf("Scenario #%d:\n",kase++);
		if(Win(s)==0)puts("There is no winning move.");
		else
		{
			printf("The winning moves are:");
			for(int i=2;i<=20;i++)if((s&(1<<i))&&Win(Choose(s,i))==0)printf(" %d",i);
			puts(".");
		}
		puts("");
	}
	return 0;
}
