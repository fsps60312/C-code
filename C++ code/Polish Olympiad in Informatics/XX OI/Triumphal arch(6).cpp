#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int N;
vector<int>ET[300000];
int Dfs(const int u,const int parent,const int staff)
{
	int coda=(int)ET[u].size();
	if(parent!=-1)coda--;
	coda-=staff;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)coda+=Dfs(nxt,u,staff);
	}
	return max(0LL,coda);
}
bool Solve(const int staff)
{
	return Dfs(0,-1,staff)==0;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%lld%lld",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		int l=0,r=N-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(!Solve(mid))l=mid+1;
			else r=mid;
		}
		printf("%lld\n",r);
	}
	return 0;
}
