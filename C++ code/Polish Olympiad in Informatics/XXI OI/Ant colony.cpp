#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
int N,G,K,S[1000000],A,B;
vector<int>ET[1000000];
LL Dfs(const int u,const int parent,const LL l,const LL r)
{
	if((int)ET[u].size()==1)return upper_bound(S,S+G,r)-lower_bound(S,S+G,l);
	const LL d=(LL)ET[u].size()-1LL;
	const LL nxtl=min(l*d,1000000001LL),nxtr=min((r+1LL)*d-1LL,1000000000LL);
	LL ans=0LL;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)ans+=Dfs(ET[u][i],u,nxtl,nxtr);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&G,&K)==3)
	{
		for(int i=0;i<G;i++)scanf("%d",&S[i]);
		sort(S,S+G);
		for(int i=0;i<N;i++)ET[i].clear();
		scanf("%d%d",&A,&B),--A,--B;
		ET[A].push_back(B),ET[B].push_back(A);
		for(int i=1,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		LL ans=0LL;
		ans+=Dfs(A,B,K,K);
		ans+=Dfs(B,A,K,K);
		printf("%lld\n",ans*K);
	}
	return 0;
}
