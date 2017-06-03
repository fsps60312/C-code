#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
struct DisjointSets
{
	int S[500000];
	void Clear(const int n){for(int i=0;i<n;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	void Merge(const int a,const int b){S[Find(a)]=Find(b);}
}DJ;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _to,const int _cost):to(_to),cost(_cost){}
};
int N,M,P[500000],POL[500000];
vector<Edge>ET[500000];
int Dfs(const int u,const int police)
{
	if(POL[u]!=-1)
	{
		if(POL[u]==police)return 0;
		return (police<POL[u]?1:-1);
	}
	if(police<0)return 1;
	if(police>P[u])return -1;
	POL[u]=police;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		const int result=Dfs(e.to,e.cost-police);
		if(result!=0)return -result;
	}
	return 0;
}
int Check(const int p)
{
	for(int i=0;i<N;i++)POL[i]=-1;
	return Dfs(0,p);
}
pair<LL,LL>Solve()
{
	pair<LL,LL>ans;
	int l=0,r=P[0];
	while(l<r)
	{
		const int mid=(l+r)/2;
//		printf("Check(%d)=%d\n",mid,Check(mid));
		if(Check(mid)==1)l=mid+1;
		else r=mid;
	}
	if(Check(r)!=0)return make_pair(-1LL,-1LL);
	ans.first=0;
	for(int i=0;i<N;i++)ans.first+=P[i]-POL[i];
	l=0,r=P[0];
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(Check(mid)==-1)r=mid-1;
		else l=mid;
	}
	assert(Check(r)==0);
	ans.second=0;
	for(int i=0;i<N;i++)ans.second+=P[i]-POL[i];
	if(ans.first>ans.second)swap(ans.first,ans.second);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&P[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b,cost;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&cost),a--,b--;
			ET[a].push_back(Edge(b,cost));
			ET[b].push_back(Edge(a,cost));
		}
		const pair<LL,LL>&ans=Solve();
		if(ans.first==-1)puts("NIE");
		else printf("%lld %lld\n",ans.first,ans.second);
	}
	return 0;
}
