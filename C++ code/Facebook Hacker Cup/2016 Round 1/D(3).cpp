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
bool Valid(const vector<int>&seq,const int avail)
{
	for(const int v:seq)if(!(avail&(1<<v)))return false;
	return true;
}
bool DP[16][5][1<<16],VIS[16][5][1<<16];
bool Solve(const int source,const int mustwin,const int avail)
{
	bool &ans=DP[source][mustwin][avail];
	if(VIS[source][mustwin][avail])return ans;
	VIS[source][mustwin][avail]=true;
	assert((1<<source)&avail);
	assert(CntBit(avail)==(1<<mustwin));
//	printf("(%d,%d,%d)\n",source,mustwin,avail);
	if(mustwin==0)return ans=true;
	for(int s=avail;s;s=(s-1)&avail)if(!(s&(1<<source))&&CntBit(s)==(1<<(mustwin-1)))
	{
		for(int i=0;i<N;i++)if((s&(1<<i))&&(WIN[source]&(1<<i)))
		{
			if(Solve(source,mustwin-1,avail^s)&&Solve(i,mustwin-1,s))return ans=true;
		}
	}
	return ans=false;
}
int Solve(const int source)
{
	for(int mustwin=L;;mustwin--)
	{
		assert(mustwin>=0);
		for(int s=0;s<(1<<N);s++)if(CntBit(s)==(1<<mustwin)&&(s&(1<<source)))
		{
//			printf("s=%d(%d,%d,%d)\n",s,source,mustwin,s);
			if(Solve(source,mustwin,s))return RANK[L-mustwin];
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(1,"%d",&N);
		L=Log(N);
//		printf("N=%d,L=%d\n",N,L);
		for(int i=0;i<N;i++)for(int j=0;j<=L;j++)for(int k=0;k<(1<<N);k++)VIS[i][j][k]=false;
		for(int i=0,v;i<N;i++)
		{
			WIN[i]=0;
			for(int j=0;j<N;j++)scanf(1,"%d",&v),WIN[i]+=v<<j;
		}
		static int kase=1;
		printf("Case #%d:\n",kase++);
		for(int i=0;i<N;i++)
		{
			printf("%d %d\n",Solve(i),RANK[WIN[i]+(1<<i)==(1<<N)-1?0:L]);
		}
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
