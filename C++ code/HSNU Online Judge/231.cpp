#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
int N,M,K;
struct Edge
{
	int a,b;
	bool inuse;
	Edge(){}
	Edge(const int &a,const int &b):a(a),b(b),inuse(false){}
};
vector<Edge>CONCRETE,PEBBLE;
struct Djset
{
	int s[20000];
	int Find(const int &a){return s[a]==a?a:(s[a]=Find(s[a]));}
	void clear(const int &n){for(int i=0;i<n;i++)s[i]=i;}
	bool Merge(const int &a,const int &b){if(Find(a)==Find(b))return false;s[Find(a)]=Find(b);return true;}
}DJ,TDJ;
int G[20000];
bool Solve()
{
	if(PEBBLE.size()<K)return false;
	DJ.clear(N);
	for(int i=0;i<CONCRETE.size();i++)
	{
		Edge &e=CONCRETE[i];
		DJ.Merge(e.a,e.b);
	}
	map<int,int>idx;
	int gn=0;
	for(int i=0;i<N;i++)
	{
		const int u=DJ.Find(i);
		if(idx.find(u)==idx.end())idx[u]=gn++;
		G[i]=idx[u];
	}
	DJ.clear(N);
	TDJ.clear(gn);
	int now=0,cnt=N;
	for(int i=0;i<PEBBLE.size();i++)
	{
		Edge &e=PEBBLE[i];
		if(TDJ.Merge(G[e.a],G[e.b]))
		{
			assert(DJ.Merge(e.a,e.b));
			e.inuse=true,now++,gn--,cnt--;
		}
	}
	assert(gn==1);
	if(now>K)return false;
	for(int i=0;i<PEBBLE.size()&&now<K;i++)
	{
		Edge &e=PEBBLE[i];
		if(e.inuse)continue;
		if(DJ.Merge(e.a,e.b))e.inuse=true,now++,cnt--;
	}
	if(now!=K)return false;
//	for(int i=0;i<PEBBLE.size()&&now<K;i++)
//	{
//		Edge &e=PEBBLE[i];
//		if(e.inuse)continue;
//		assert(!DJ.Merge(e.a,e.b));
//		e.inuse=true,now++;
//	}
	assert(now==K);
	for(int i=0;i<CONCRETE.size();i++)
	{
		Edge &e=CONCRETE[i];
		if(DJ.Merge(e.a,e.b))e.inuse=true,cnt--;
	}
	assert(cnt==1);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	assert(N<20000);
	CONCRETE.clear(),PEBBLE.clear();
	for(int i=0;i<M;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==b)continue;
		a--,b--;
		assert(a>=0&&a<N&&b>=0&&b<N);
		if(c==0)CONCRETE.push_back(Edge(a,b));
		else if(c==1)PEBBLE.push_back(Edge(a,b));
		else assert(0);
	}
	if(!Solve())puts("no solution");
	else
	{
		int cnt=0;
		for(int i=0;i<PEBBLE.size();i++)
		{
			Edge &e=PEBBLE[i];
			if(!e.inuse)continue;
			printf("%d %d 1\n",e.a+1,e.b+1);
			cnt++;
		}
		assert(cnt==K);
		for(int i=0;i<CONCRETE.size();i++)
		{
			Edge &e=CONCRETE[i];
			if(!e.inuse)continue;
			printf("%d %d 0\n",e.a+1,e.b+1);
			cnt++;
		}
		assert(cnt==N-1);
	}
	return 0;
}
