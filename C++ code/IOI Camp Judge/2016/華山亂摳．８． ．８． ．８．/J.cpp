#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
int N,FA[100000],A[100000];
set<int>ET[100000];
int GetSize(const int u)
{
	assert(A[u]==0);
	int ans=1;
	for(const int nxt:ET[u])ans+=GetSize(nxt);
	return ans;
}
bool Solve()
{
	int ans=0;
	for(int i=0;i<N;i++)if(A[i]==1)
	{
		int sz=0;
		for(const int nxt:ET[i])sz+=GetSize(nxt);
		if(sz==0)return true;
		ans+=sz-1;
	}
	if(ans%2==1)return true;
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1;i<N;i++)scanf("%d",&FA[i]),ET[FA[i]].insert(i);
		for(int i=0;i<N;i++)scanf("%d",&A[i]),TAG[i]=false;
//		for(int i=1;i<N;i++)if(A[i]==1)
//		{
//			for(int u=i;u!=0;)
//			{
//				ET[FA[u]].erase(u);
//				if(!ET[FA[u]].empty())break;
//				u=FA[u];
//				TAG[u]=0;
//			}
//		}
		puts(Solve()?"689":"bBg");
	}
	return 0;
}
