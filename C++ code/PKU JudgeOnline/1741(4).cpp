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
int GetSize(const int u,const int fa)
{
	assert(!VIS[u]);
	int ans=1;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||VIS[nxt])continue;
		ans+=GetSize(nxt,u);
	}
	return ans;
}
int FindCentroid(const int u,const int fa,const int n,int &mn,int &ans)
{
	assert(!VIS[u]);
	int sz=1,tmn=-INF;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||VIS[nxt])continue;
		const int chsz=FindCentroid(nxt,u,n,mn,ans);
		sz+=chsz;
		getmax(tmn,chsz);
	}
	getmax(tmn,n-sz);
	if(tmn<mn)mn=tmn,ans=u;
	return sz;
}
int FindCentroid(const int source)
{
	int mn=INF,ans=-1;
	FindCentroid(source,-1,GetSize(source,-1),mn,ans);
	return ans;
}
void BuildPath(const int u,const int fa,const int plen,vector<int>&path)
{
	if(plen>K)return;
	path.push_back(plen);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||VIS[nxt])continue;
		BuildPath(nxt,u,plen+e.cost,path);
	}
}
int SetRoot(const int root)
{
	int ans=0;
	VIS[root]=true;
	for(int i=0;i<(int)ET[root].size();i++)
	{
		const Edge &e=EDGE[ET[root][i]];
		const int nxt=(e.a==root?e.b:e.a);
		if(VIS[nxt])continue;
		ans+=SetRoot(FindCentroid(nxt));
	}
	vector<int>path;
	for(int i=0;i<(int)ET[root].size();i++)
	{
		const Edge &e=EDGE[ET[root][i]];
		const int nxt=(e.a==root?e.b:e.a);
		if(VIS[nxt])continue;
		vector<int>tpath;
		BuildPath(nxt,-1,e.cost,tpath);
		sort(tpath.begin(),tpath.end());
		for(int l=0,r=(int)tpath.size()-1;;l++)
		{
			while(r>l&&tpath[r]+tpath[l]>K)r--;
			if(r<=l)break;
			ans-=r-l;
		}
		for(int j=0;j<(int)tpath.size();j++)path.push_back(tpath[j]);
	}
	VIS[root]=false;
//	printf("root=%d,sz=%d\n",root,(int)path.size());
	sort(path.begin(),path.end());
//	for(const int v:path)printf("%d ",v);puts(""); 
	for(int l=0,r=(int)path.size()-1;;l++)
	{
		while(r>l&&path[r]+path[l]>K)r--;
		if(r<=l)break;
		ans+=r-l;
	}
	ans+=path.size();
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
