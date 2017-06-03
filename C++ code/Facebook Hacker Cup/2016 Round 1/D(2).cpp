#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int CntBit(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
int Log(int n){int ans=0;while(n>>=1)ans++;return ans;}
int N,L;
int WIN[16];
int RANK[5]={1,2,3,5,9};
bool DP[16][5][1<<16];
vector<int>SET[16];
int Solve(const int source)
{
	for(int i=L;;i--)
	{
		assert(i>=0);
		if(DP[source][i][((1<<N)-1)-(1<<source)])return RANK[L-i];
	}
}
int main()
{
	for(int i=0;i<(1<<16);i++)SET[CntBit(i)].push_back(i);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(1,"%d",&N);
		L=Log(N);
		for(int i=0,v;i<N;i++)
		{
			WIN[i]=0;
			for(int j=0;j<N;j++)scanf(1,"%d",&v),WIN[i]+=v<<j;
		}
		for(int i=0;i<N;i++)for(int j=0;j<=L;j++)for(const int s:SET[j])DP[i][j][s]=false;
		for(int mustwin=0;mustwin<=L;mustwin++)
		{
			for(int i=0;i<N;i++)
		}
		for(int i=0;i<N;i++)
		{
			printf("%d %d\n",Solve(i),RANK[WIN[i]+(1<<i)+1==(1<<N)?0:L]);
		}
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
