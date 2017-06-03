#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	const int a,b;
	Edge():a(),b(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
struct Djset
{
	int s[100000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
	int operator[](const int a){return find(a);}
}ID,COMP;
vector<int>ET[100000];
int PARENT[100000],DEPTH[100000];
void MarkParent(const int u,const int parent,const int depth)
{
	assert(PARENT[u]==-2);
	PARENT[u]=parent,DEPTH[u]=depth;
	for(const int nxt:ET[u])if(nxt!=parent)MarkParent(nxt,u,depth+1); 
}
int N,K,M;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		EDGE.clear();
		for(int a,b,i=0;i<K;i++)scanf("%d%d",&a,&b),EDGE.push_back(Edge(--a,--b));
		scanf("%d",&M);
		for(int a,b,i=0;i<M;i++)scanf("%d%d",&a,&b),EDGE.push_back(Edge(--a,--b));
		for(int i=0;i<N;i++)ET[i].clear();
		COMP.clear(N);
		for(const Edge &e:EDGE)if(COMP.merge(e.a,e.b))ET[e.a].push_back(e.b),ET[e.b].push_back(e.a);
		for(int i=0;i<N;i++)PARENT[i]=-2;
		for(int u=0;u<N;u++)if(PARENT[u]==-2)MarkParent(u,-1,0);
		COMP.clear(N);
		ID.clear(N);
		assert(K+M==(int)EDGE.size());
		for(int i=0,ans=0;i<K+M;i++)
		{
			const Edge &e=EDGE[i];
			int a=ID[e.a],b=ID[e.b];
			if(a!=b)
			{
				if(COMP[a]!=COMP[b])COMP.merge(a,b),ans++;
				else
				{
					while(a!=b)
					{
						if(DEPTH[b]>DEPTH[a])swap(a,b);
						assert(DEPTH[a]>=DEPTH[b]);
						ID.merge(a,PARENT[a]),a=ID[a],ans--;
					}
				}
			}
			if(i>=K)printf("%d\n",ans);
		}
	}
	return 0;
}
