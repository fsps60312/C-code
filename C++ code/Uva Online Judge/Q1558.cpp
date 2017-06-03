#include<cstdio>
#include<cassert>
using namespace std;
int T,N;
int DP[1<<21];
int Win(const int s)
{
	int &dp=DP[s];
	if(dp!=-1)return dp;
	for(int i=1;i<=20;i++)if((s&(1<<i)))
	{
		int ts=s;
		for(int j=0;j<=20;j++)if(!(s&(1<<j)))
		{
			for(int cnt=1;j+i*cnt<=20;cnt++)ts&=~(1<<(j+i*cnt));
		}
		if(Win(ts)==0)return dp=1;
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
		for(int i=0,v;i<N;i++)scanf("%d",&v),s|=(1<<v),assert(v>=1&&v<=20);
		static int kase=1;
		printf("Scenario #%d:\n",kase++);
		if(Win(s)==0)puts("There is no winning move.");
		else
		{
			printf("The winning moves are:");
			for(int i=1;i<=20;i++)if((s&(1<<i))&&Win(s-(1<<i))==0)printf(" %d",i);
			puts(".");
		}
		puts("");
	}
	return 0;
}
