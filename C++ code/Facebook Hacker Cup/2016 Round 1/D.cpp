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
bool Solve(const int source,const int mustwin,const int avail);
bool Solve(const int source,const int mustwin,const int avail)
{
	for(int s=avail;s;s=avail&(s-1))if(CntBit(s)==mustwin)
	{
		vector<int>seq;
		for(int i=0;i<N;i++)if(s&(1<<i))seq.push_back(i);
		sort(seq.begin(),seq.end());
		do
		{
			
		}while(next_permutation(seq.begin(),seq.end()));
	}
	return false;
}
int Solve(const int source)
{
	for(int i=L;;i--)
	{
		assert(i>=0);
		if(Solve(source,i,((1<<N)-1)-(1<<source)))return RANK[L-i];
	}
}
int main()
{
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
		for(int i=0;i<N;i++)
		{
			printf("%d %d\n",Solve(i),RANK[WIN[i]+(1<<i)+1==(1<<N)?0:L]);
		}
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
