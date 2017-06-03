#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,K;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
vector<int>ET[10000];
bool VIS[10000];
int FindCentroid(const int u,const int fa,int &mn,int &ans)
{
	assert(!VIS[u]);
	int sz=1,tmn=-INF;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||VIS[nxt])continue;
		const int chsz=FindCentroid(nxt,u,mn,ans);
		sz+=chsz;
		getmax(tmn,chsz);
	}
	getmax(tmn,N-sz);
	if(tmn<mn)mn=tmn,ans=u;
	return sz;
}
int FindCentroid(const int source)
{
	int mn=INF,ans=-1;
	FindCentroid(source,-1,mn,ans);
	return ans;
}
void BuildPath(const int u,const int fa,const int plen,vector<int>&path)
{
	path.push_back(plen);
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||VIS[nxt])continue;
		BuildPath(nxt,u,plen+e.cost,path);
	}
}
int Rank(const vector<int>&s,const int v){return upper_bound(s.begin(),s.end(),v)-s.begin();}
int SetRoot(const int root)
{
	int ans=0;
	VIS[root]=true;
	for(const int ei:ET[root])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==root?e.b:e.a);
		if(VIS[nxt])continue;
		ans+=SetRoot(FindCentroid(nxt));
	}
	VIS[root]=false;
	vector<vector<int> >chpaths;
	vector<int>path;
	for(const int ei:ET[root])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==root?e.b:e.a);
		if(VIS[nxt])continue;
		vector<int>tpath;
		BuildPath(nxt,root,e.cost,tpath);
		sort(tpath.begin(),tpath.end());
		chpaths.push_back(tpath);
		for(const int v:tpath)path.push_back(v);
	}
//	printf("root=%d,sz=%d\n",root,(int)path.size());
	sort(path.begin(),path.end());
//	for(const int v:path)printf("%d ",v);puts(""); 
	if(true)
	{
		int ta=0;
		for(const auto &a:chpaths)for(const int v:a)ta+=Rank(path,K-v)-(Rank(a,K-v));
		assert(ta%2==0);
		ans+=ta/2;
	}
	ans+=Rank(path,K);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		if(N==0&&K==0)break;
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		EDGE.clear();
		for(int i=0,a,b,c;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		printf("%d\n",SetRoot(FindCentroid(0)));
	}
	return 0;
}
