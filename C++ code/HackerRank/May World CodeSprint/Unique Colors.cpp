#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N,C[100000],CNT[100000];
vector<int>ET[100000];
void Dfs(const int u,const int parent,LL &now,LL &ans)
{
	if(!CNT[C[u]]++)++now;
	ans+=now;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		Dfs(nxt,u,now,ans);
	}
	if(!--CNT[C[u]])--now;
}
LL Solve(const int u)
{
	LL ans=0LL,now=0LL;
	Dfs(u,-1,now,ans);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]),--C[i],ET[i].clear();
		for(int i=0;i<100000;i++)CNT[i]=0;
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),--a,--b,ET[a].push_back(b),ET[b].push_back(a);
		for(int i=0;i<N;i++)printf("%lld\n",Solve(i));
	}
	return 0;
}
