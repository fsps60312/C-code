#include<cstdio>
#include<cassert>
#include<set>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,S[30];
bool Solve()
{
	const int half=N/2;
	set<int>sum;
	for(int s=1;s<(1<<half);s++)
	{
		int tmp=0;
		for(int i=0;i<half;i++)if(s&(1<<i))tmp+=S[i];
		if(tmp==0)return true;
		sum.insert(tmp);
	}
	for(int s=1;s<(1<<(N-half));s++)
	{
		int tmp=0;
		for(int i=half;i<N;i++)if((s<<half)&(1<<i))tmp+=S[i];
		if(tmp==0||sum.find(-tmp)!=sum.end())return true;
	}
	return false;
}
int main()
{
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)scanf(1,"%d",&S[i]);
	puts(Solve()?"yes":"no");
	return 0;
}
