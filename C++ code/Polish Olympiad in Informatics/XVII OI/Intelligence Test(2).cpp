#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int M;
vector<int>LOCS[1000001];
bool Solve()
{
	static int n,s[1000000];
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&s[i]);
	for(int i=0,cur=0;i<n;i++)
	{
		const vector<int>&loc=LOCS[s[i]];
		const vector<int>::const_iterator it=lower_bound(loc.begin(),loc.end(),cur);
		if(it==loc.end())return false;
		cur=*it+1;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&M)==1)
	{
		for(int i=1;i<=1000000;i++)LOCS[i].clear();
		for(int i=0,v;i<M;i++)scanf("%d",&v),LOCS[v].push_back(i);
		int n;scanf("%d",&n);
		while(n--)puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
