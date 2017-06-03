#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
map<int,LL,greater<LL> >AVAIL;
bool Get(const LL &v,const int i){return (v&(1LL<<i))>0LL;}
void UniqueLinear(vector<LL>&s)
{
	for(int c=60,r=0;c>=0&&r<(int)s.size();)
	{
		if(!Get(s[r],c))
		{
			bool found=false;
			for(int i=r+1;i<(int)s.size();i++)if(Get(s[i],c)){swap(s[r],s[i]),found=true;break;}
			if(!found){c--;continue;}
		}
		for(int i=0;i<(int)s.size();i++)if(i!=r&&Get(s[i],c))s[i]^=s[r];
		c--,r++;
	}
	sort(s.begin(),s.end(),greater<LL>());
	for(int i=(int)s.size()-1;i>=0&&s[i]==0LL;i--)s.pop_back();
	assert(s.size()<=60);
	AVAIL.clear();
	for(const LL &v:s)
	{
		for(int i=60;;i--)
		{
			assert(i>=0);
			if(Get(v,i)){assert(AVAIL.find(i)==AVAIL.end()),AVAIL[i]=v;break;}
		}
	}
}
struct Djset
{
	int s[50000];
	LL dist[50000];
	vector<int>member[50000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i,dist[i]=0LL,member[i].clear(),member[i].push_back(i);}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b,LL cost)
	{
		cost^=(dist[a]^dist[b]);
		if((a=Find(a))==(b=Find(b)))return false;
		if(member[a].size()>member[b].size())swap(a,b);
		for(const int v:member[a])member[b].push_back(v),dist[v]^=cost;
		member[a].clear(),vector<int>().swap(member[a]);
		s[a]=b;
		return true;
	}
};
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int _a,const int _b,const LL &_cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
vector<int>ET[50000];
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	vector<LL>cycle;
	LL ans;
	if(true)
	{
		static Djset dj;dj.clear(N);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			static LL cost;
			scanf("%d%d%lld",&a,&b,&cost),a--,b--;
			EDGE.push_back(Edge(a,b,cost));
			ET[a].push_back(i),ET[b].push_back(i);
			if(!dj.Merge(a,b,cost))cycle.push_back(cost^dj.dist[a]^dj.dist[b]);
		}
		ans=(dj.dist[0]^dj.dist[N-1]);
	}
	UniqueLinear(cycle);
	for(const auto &it:AVAIL)if(!Get(ans,it.first))ans^=it.second;
	printf("%lld\n",ans);
	return 0;
}
