#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,K,S[1000000];
int Solve()
{
	vector<int>loc;
	loc.push_back(-1);
	for(int i=0;i<N;i++)if(S[i]<K)loc.push_back(i);
	loc.push_back(N);
	int ans=0;
	for(int i=1;i<(int)loc.size();i++)getmax(ans,loc[i]-1-loc[i-1]);
	for(int i=1;i+1<(int)loc.size();i++)
	{
		if(loc[i]&&S[loc[i]]+S[loc[i]-1]>=K*2)getmax(ans,loc[i+1]-1-loc[i-1]);
		else if(loc[i]+1<N&&S[loc[i]]+S[loc[i]+1]>=K*2)getmax(ans,loc[i+1]-1-loc[i-1]);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int querycount;
	scanf(2,"%d%d",&N,&querycount);
	for(int i=0;i<N;i++)scanf(1,"%d",&S[i]);
	for(int qcnt=0;qcnt<querycount;qcnt++)
	{
		if(qcnt)putchar(' ');
		scanf(1,"%d",&K);
		printf("%d",Solve());
	}
	puts("");
	return 0;
}
