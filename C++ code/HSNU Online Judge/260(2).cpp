#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
bool getmax(int &a,const int b){if(b>a){a=b;return true;}return false;}
bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int N,K;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[200000];
bool VIS[200000];
int SZ[200000],MX[200000];
int GetSz(const int u,const int fa,vector<int>&rec)
{
	if(VIS[u])return 0;
	MX[u]=-INF;
	rec.push_back(u);
	int &sz=SZ[u]=1;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==fa)continue;
		const int chsz=GetSz(nxt,u,rec);
		sz+=chsz;
		getmax(MX[u],chsz);
	}
	return sz;
}
int GetWeightPoint(const int source)
{
	assert(!VIS[source]);
	vector<int>rec;
	GetSz(source,-1,rec);
	assert(!rec.empty());
//	printf("sz=%d\n",rec.size());
	int ans=-1,mxch=INF;
	for(const auto u:rec)if(getmin(mxch,max((int)rec.size()-SZ[u],MX[u])))ans=u;
	assert(ans!=-1);
	return ans;
}
void GetDep(const int u,const int fa,const int cost,const int cnt,map<int,int>&deps)
{
	if(VIS[u]||cost>K)return;
	auto it=deps.find(cost);
	if(it==deps.end())deps[cost]=cnt;
	else getmin(it->second,cnt);
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==fa)continue;
		GetDep(nxt,u,cost+e.cost,cnt+1,deps);
	}
}
int ANS;
void SetCenter(const int root)
{
//	printf("root=%d\n",root);
	assert(!VIS[root]);
	VIS[root]=true;
	map<int,int>all;
	vector<int>ch;
	for(int i=0;i<ET[root].size();i++)
	{
		const Edge &e=EDGE[ET[root][i]];
		const int nxt=(root==e.a?e.b:e.a);
		if(VIS[nxt])continue;
		ch.push_back(nxt);
		map<int,int>deps;
		GetDep(nxt,root,e.cost,1,deps);
		for(auto d:deps)
		{
			assert(d.first<=K);
			if(d.first==K)getmin(ANS,d.second);
			else
			{
				auto it=all.find(K-d.first);
				if(it!=all.end())getmin(ANS,d.second+it->second);
			}
		}
		for(auto d:deps)if(d.first<K)
		{
			auto it=all.find(d.first);
			if(it==all.end())all.insert(d);
			else getmin(it->second,d.second);
		}
	}
	for(const int u:ch)SetCenter(GetWeightPoint(u));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		EDGE.clear();
		for(int i=0,a,b,c;i+1<N;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		ANS=INF;
		SetCenter(GetWeightPoint(0));
		if(ANS==INF)ANS=-1;
		printf("%d\n",ANS);
//		break;
	}
	return 0;
}
