#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
LL X,Y;
vector<int>ET[200000];
pair<int,int>PATH_COUNT[200000];
const pair<int,int>&GetMinPathCount(const int u,const int parent)
{
	pair<int,int>&ans=PATH_COUNT[u];
	if(ans.first!=-1)return ans;
	vector<pair<int,int> >dp;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		dp.push_back(GetMinPathCount(nxt,u));
	}
	if(dp.empty())return ans=make_pair(1,1);
	sort(dp.begin(),dp.end(),[](const pair<int,int>&a,const pair<int,int>&b)->bool{return a.second-a.first<b.second-b.first;});
	if(true)
	{
		if((int)dp.size()==1)ans.first=dp[0].second;
		else
		{
			ans.first=dp[0].second+dp[1].second-1;
			for(int i=2;i<(int)dp.size();i++)ans.first+=dp[i].first;
		}
	}
	if(true)
	{
		ans.second=dp[0].second;
		for(int i=1;i<(int)dp.size();i++)ans.second+=dp[i].first;
	}
	return ans;
}
LL Solve()
{
	if(X<Y)
	{
		for(int i=0;i<N;i++)PATH_COUNT[i].first=-1;
		const int ans=GetMinPathCount(0,-1).first;
		return Y*(ans-1LL)+X*(N-ans);
	}
	else
	{
		for(int i=0;i<N;i++)if((int)ET[i].size()==N-1)return X+Y*(N-2LL);
		return Y*(N-1LL);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%I64d%I64d",&N,&X,&Y)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		printf("%I64d\n",Solve());
	}
	return 0;
}
