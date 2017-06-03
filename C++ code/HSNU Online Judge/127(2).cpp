#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
LL SUM[1000001];
int N,K,S[1000001];
int Solve()
{
	SUM[0]=0LL;
	for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+(S[i]-K);
	int ans=0;
	map<LL,int>low;
	low[0LL]=0;
	for(int i=1;i<=N;i++)
	{
		auto it=low.upper_bound(SUM[i]);
		if(it==low.begin())low[SUM[i]]=i;
		else getmax(ans,i-((--it)->second));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int querycount;
	scanf(2,"%d%d",&N,&querycount);
	for(int i=1;i<=N;i++)scanf(1,"%d",&S[i]);
	for(int qcnt=0;qcnt<querycount;qcnt++)
	{
		if(qcnt)putchar(' ');
		scanf(1,"%d",&K);
		printf("%d",Solve());
	}
	puts("");
	return 0;
}
