#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
vector<int>ET[200];
bool VIS[200],GUARD[200];
bool Dfs(const int u,const int fa,const bool place,int &a,int &b)
{
	assert(!VIS[u]);
	(place?a:b)++;
	GUARD[u]=place;
	VIS[u]=true;
	for(const auto nxt:ET[u])if(nxt!=fa)
	{
		if(VIS[nxt])
		{
			if(place==GUARD[nxt])return false;
		}
		else if(!Dfs(nxt,u,place^true,a,b))return false;
	}
	return true;
}
int Solve()
{
	int ans=0;
	for(int i=0;i<N;i++)if(!VIS[i])
	{
		int a=0,b=0;
		if(!Dfs(i,-1,true,a,b))return -1;
		ans+=max(1,min(a,b));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
			assert(a>=0&&a<N&&b>=0&&b<N);
			ET[a].push_back(b),ET[b].push_back(a);
		}
		printf("%d\n",Solve());
	}
	assert(scanf("%d",&casecount)!=1);
}
