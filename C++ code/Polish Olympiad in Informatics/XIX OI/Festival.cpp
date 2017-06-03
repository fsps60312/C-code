#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
struct DisjointSets
{
	int DATA[600],HEIGHT[600];
	void Clear(const int n){for(int i=0;i<n;i++)DATA[i]=i,HEIGHT[i]=0;}
	int Find(const int a)
	{
		if(DATA[a]==a)return a;
		const int parent=DATA[a];
		DATA[a]=Find(DATA[a]);
		HEIGHT[a]+=HEIGHT[parent];
		return DATA[a];
	}
	bool Merge(const int _a,const int _b)
	{
		const int a=Find(_a),b=Find(_b);
		if(a==b)return HEIGHT[a]+1==HEIGHT[b];
		assert(HEIGHT[a]==0&&HEIGHT[b]==0);
		HEIGHT[a]=HEIGHT[_b]-HEIGHT[_a]-1;
		DATA[a]=b;
		return true;
	}
	int Height(const int a){return HEIGHT[Find(a)];}
}DJ;
int N,M1,M2;
vector<int>ET[600];
bool BellmonFord(int *dists)
{
	static int cnt[600];
	static bool inq[600];
	for(int i=0;i<N;i++)dists[i]=DJ.Height(i),cnt[i]=0,inq[i]=false;
	queue<int>q;
	for(int i=0;i<N;i++)q.push(i),inq[i]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();inq[u]=false;
		if(++cnt[u]>N)return false;
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			const int dist=dists[u]+DJ.Height(nxt)-DJ.Height(u);
			if(dist>dists[nxt])
			{
				dists[nxt]=dist;
				if(!inq[nxt])q.push(nxt),inq[nxt]=true;
			}
		}
	}
	return true;
}
bool Solve(int *dists)
{
	DJ.Clear(N);
	for(int i=0,a,b;i<M1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		if(!DJ.Merge(a,b))return false;
	}
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M2;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b);
	}
	for(int i=0;i<N;i++)sort(ET[i].begin(),ET[i].end()),ET[i].resize(unique(ET[i].begin(),ET[i].end())-ET[i].begin());
	if(!BellmonFord(dists))return false;
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M1,&M2);
	static int dists[600];
	if(!Solve(dists))puts("NIE");
	else
	{
		for(int i=0;i<N;i++)dists[i]-=DJ.Height(i);
		int mn=INF,mx=-INF;
		for(int i=0;i<N;i++)
		{
			if(dists[i]<mn)mn=dists[i];
			if(dists[i]>mx)mx=dists[i];
		}
		printf("%d\n",mx-mn+1);
	}
	return 0;
}
