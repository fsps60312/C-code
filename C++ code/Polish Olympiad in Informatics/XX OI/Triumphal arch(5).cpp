#include<cstdio>
#include<cassert>
#include<vector>
#define int long long
using namespace std;
int N;
vector<int>ET[300000];
int DP[300000];
void Dfs1(const int u,const int parent,const int staff)
{
	DP[u]=staff-((int)ET[u].size()-1);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			Dfs1(nxt,u,staff);
			const int ta=DP[nxt]+staff;
			if(ta<0)DP[u]+=ta;
		}
	}
}
bool Dfs2(const int u,const int parent,const int staff,const int coda)
{
	vector<int>nxts,costs;
	int sum=0;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			nxts.push_back(nxt);
			const int ta=min(0LL,DP[nxt]+staff);
			costs.push_back(ta);
			sum+=ta;
		}
	}
	if(coda+sum<0)return false;
	for(int i=0;i<(int)nxts.size();i++)
	{
		if(!Dfs2(nxts[i],u,staff,coda+(staff-((int)ET[nxts[i]].size()-1))+(sum-costs[i])))return false;
	}
	return true;
}
bool Solve(const int staff)
{
	Dfs1(0,-1,staff);
	return Dfs2(0,-1,staff,staff-(int)ET[0].size());
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
